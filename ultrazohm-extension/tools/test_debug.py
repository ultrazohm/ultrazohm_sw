import importlib.util
import json
from io import BytesIO
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import Mock, patch

ROOT = Path(__file__).resolve().parents[1]
TCL = os.environ.get('UZ_TEST_TCL', 'tclsh')

def load(name, file):
    spec = importlib.util.spec_from_file_location(name, ROOT / file)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

flash = load('flash_debug_test', 'flash.py')
proxy = load('xsct_debug_test', 'debug-xsct.py')
adapter = load('adapter_debug_test', 'debug-adapter.py')

class DebugTest(unittest.TestCase):
    def test_adapter_forwards_launch_and_forces_detach_on_stop(self):
        messages=[{'seq': 1, 'type': 'request', 'command': 'initialize', 'arguments': {'adapterID': 'ultrazohm-gdb'}},
                  {'seq': 2, 'type': 'request', 'command': 'launch', 'arguments': {'type': 'ultrazohm-gdb', 'stopAtConnect': True}},
                  {'seq': 3, 'type': 'request', 'command': 'disconnect', 'arguments': {'terminateDebuggee': True}}]
        source=BytesIO()
        for message in messages:
            body=json.dumps(message).encode()
            source.write(b'Content-Length: '+str(len(body)).encode()+b'\r\n\r\n'+body)
        source.seek(0)
        destination=BytesIO()
        adapter.forward_requests(source,destination)
        destination.seek(0)
        received=[]
        for _ in messages:
            length=int(destination.readline().split(b':')[1]);destination.readline()
            received.append(json.loads(destination.read(length)))
        self.assertEqual(received[0]['arguments']['adapterID'],'cppdbg')
        self.assertEqual(received[1]['arguments'],{'type':'cppdbg','stopAtConnect':True})
        self.assertEqual(received[2]['arguments']['terminateDebuggee'],False)
        self.assertEqual(received[2]['seq'],3)

    def test_source_breakpoints_are_scoped_to_each_core(self):
        with tempfile.TemporaryDirectory() as root:
            for core, own, other in [('R5', 'Baremetal', 'FreeRTOS'), ('A53', 'FreeRTOS', 'Baremetal')]:
                source, destination, responses = BytesIO(), BytesIO(), []
                adapter.write_message(source, {'seq': 1, 'type': 'request', 'command': 'launch',
                    'arguments': {'ultrazohmRepository': root, 'ultrazohmCore': core}})
                paths = [f'vitis/software/{other}/src/sw/isr.c',
                         f'vitis/software/{own}/src/sw/isr.c',
                         'vitis/software/shared/shared.c',
                         f'vitis/workspace/{other}/src/isr.c',
                         f'vitis/software/{other}Extra/isr.c']
                for seq, path in enumerate(paths, 2):
                    adapter.write_message(source, {'seq': seq, 'type': 'request', 'command': 'setBreakpoints',
                        'arguments': {'source': {'path': str(Path(root) / path)},
                                      'breakpoints': [{'line': 70}, {'line': 80}]}})
                # Removing another core's breakpoints must not reach GDB either.
                adapter.write_message(source, {'seq': 7, 'type': 'request', 'command': 'setBreakpoints',
                    'arguments': {'source': {'path': str(Path(root) / paths[0])}, 'breakpoints': []}})
                source.seek(0)
                adapter.forward_requests(source, destination, responses.append)
                destination.seek(0)
                forwarded = list(adapter.messages(destination))
                self.assertEqual([m['seq'] for m in forwarded], [1, 3, 4, 6])
                self.assertEqual([m['request_seq'] for m in responses], [2, 5, 7])
                self.assertTrue(all(m['success'] for m in responses))
                self.assertEqual([b['verified'] for b in responses[0]['body']['breakpoints']], [False, False])
                self.assertEqual(responses[-1]['body']['breakpoints'], [])

    def test_request_matches_service_job_and_checkout(self):
        with tempfile.TemporaryDirectory() as directory:
            config = {'root': directory}
            request = {'service_id': 'service', 'request_id': 'debug-request'}
            status = {'repository': directory, 'service_id': 'service', 'active_job': {'request_id': 'debug-request', 'action': 'flash', 'state': 'running'}}
            self.assertTrue(proxy.matching_request(config, request, status))
            for job in [None, {'request_id': 'ordinary-flash', 'action': 'flash', 'state': 'running'}, {'request_id': 'debug-request', 'action': 'flash', 'state': 'succeeded'}]:
                self.assertFalse(proxy.matching_request(config, request, {**status, 'active_job': job}))
            self.assertFalse(proxy.matching_request(config, request, {**status, 'service_id': 'restarted'}))

    def test_debug_uses_flash_no_reconnect_and_requires_stop_proof(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            config = {'root': directory, 'endpoint': '127.0.0.1:19740', 'ticket': str(root/'request.json'), 'proof': str(root/'proof')}
            config_file=root/'bridge.json'
            config_file.write_text(json.dumps(config))
            client=Mock(endpoint=config['endpoint'])
            client.status.return_value={'repository': directory, 'firmware_available':True, 'service_id':'service', 'device_target':'192.168.1.233:1000'}
            client.firmware.return_value={'id':'job'}
            monitor=Mock(complete=True)
            monitor.poll.return_value={'log':''}
            with self.assertRaisesRegex(RuntimeError, 'not confirmed'):
                flash.flash(client,Mock(return_value=monitor),root,debug_config=config_file)
            self.assertFalse((root/'request.json').exists())
            options=client.firmware.call_args.kwargs
            self.assertTrue(options['no_reconnect'])
            self.assertEqual(options['device'],'192.168.1.233:1000')
            def proof():
                request=json.loads((root/'request.json').read_text())
                (root/'proof').write_text(request['request_id'])
                return {'log':''}
            monitor.poll.side_effect=proof
            flash.flash(client,Mock(return_value=monitor),root,debug_config=config_file)
            self.assertFalse((root/'request.json').exists())
            client.shutdown.assert_not_called()

    def test_lost_monitor_keeps_request_for_accepted_job(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory)
            config={'root':directory,'endpoint':'127.0.0.1:19740','ticket':str(root/'request.json'),'proof':str(root/'proof')}
            (root/'bridge.json').write_text(json.dumps(config))
            client=Mock(endpoint=config['endpoint'])
            client.status.return_value={'repository':directory,'firmware_available':True,'service_id':'service'}
            client.firmware.return_value={'id':'job'}
            monitor=Mock();monitor.poll.side_effect=RuntimeError('lost connection')
            with self.assertRaisesRegex(RuntimeError,'lost connection'):
                flash.flash(client,Mock(return_value=monitor),root,debug_config=root/'bridge.json')
            self.assertTrue((root/'request.json').exists())

    @unittest.skipUnless(shutil.which(TCL), 'Tcl interpreter not installed')
    def test_tcl_wraps_original_entry_and_stops_both_applications(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory)
            # Exercise the real wrapper in a Tcl interpreter with fake XSCT commands.
            fixture=r'''
# CI may have Tcl 8.6; also reproduce the command set of XSCT Tcl 8.5.
if {[llength [info commands ::try]]} { rename ::try {} }
set log [open $::env(UZ_TEST_LOG) w]
proc record {args} { puts $::log $args; flush $::log }
proc dow {args} { record dow {*}$args }
proc con {args} { record con {*}$args }
proc bpadd {args} { record bpadd {*}$args; return 7 }
proc bpremove {args} { record bpremove {*}$args }
proc print {args} { return {at_main 1} }
proc stop {} { record stop }
source $::env(UZ_TEST_WRAPPER)
'''
            (root/'fixture.tcl').write_text(fixture)
            entry=root/'entry.tcl'
            env=dict(os.environ,UZ_TEST_LOG=str(root/'log'),UZ_DEBUG_ENTRY=str(entry),UZ_TEST_WRAPPER=str(ROOT/'debug-main.tcl'),UZ_DEBUG_PROOF=str(root/'proof'),UZ_DEBUG_REQUEST='request')
            entry.write_text('dow fsbl.elf\ncon\ndow FreeRTOS/Debug/FreeRTOS.elf\ncon\nbpremove -all\ndow Baremetal/Debug/Baremetal.elf\ncon\nexit 0\n')
            result=subprocess.run([TCL,str(root/'fixture.tcl')],env=env,capture_output=True,text=True)
            self.assertEqual(result.returncode,0,result.stdout+result.stderr)
            self.assertEqual((root/'proof').read_text().strip(),'request')
            log=(root/'log').read_text().splitlines()
            self.assertEqual(log.count('con -block -timeout 30'),2)
            self.assertEqual(log.count('con'),1)
            self.assertEqual(log.count('bpadd -addr &main -type hw'),2)
            (root/'proof').unlink()
            entry.write_text('dow FreeRTOS.elf\ncon\nexit 0\n')
            result=subprocess.run([TCL,str(root/'fixture.tcl')],env=env,capture_output=True,text=True)
            self.assertEqual(result.returncode,1)
            self.assertFalse((root/'proof').exists())
            entry.write_text('proc print {args} {return {at_main 0}}\ndow FreeRTOS.elf\ncon\n')
            result=subprocess.run([TCL,str(root/'fixture.tcl')],env=env,capture_output=True,text=True)
            self.assertNotEqual(result.returncode,0)
            self.assertFalse((root/'proof').exists())
            self.assertIn('stop',(root/'log').read_text())

            # Cleanup must run on a resume failure, and its own failure must not
            # mask the original cause or produce a successful-stop receipt.
            for resume_error, cleanup_error in [(True, False), (False, True), (True, True)]:
                overrides = []
                if resume_error:
                    overrides.append('proc ::uz_debug::original_con {args} { record con {*}$args; error "resume timeout" }')
                if cleanup_error:
                    overrides.append('proc bpremove {args} { record bpremove {*}$args; error "cleanup failed" }')
                entry.write_text('\n'.join(overrides) + '\ndow FreeRTOS.elf\ncon\nexit 0\n')
                result = subprocess.run([TCL, str(root/'fixture.tcl')], env=env, capture_output=True, text=True)
                self.assertNotEqual(result.returncode, 0)
                self.assertIn('resume timeout' if resume_error else 'cleanup failed', result.stderr)
                self.assertFalse((root/'proof').exists())
                log = (root/'log').read_text().splitlines()
                self.assertIn('bpremove 7', log)
                if resume_error:
                    self.assertIn('stop', log)
