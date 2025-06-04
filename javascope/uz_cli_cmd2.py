import asyncio
import cmd2
import threading
from read_with_decode_send_receive_class import ultrazohm

class UltrazohmShell(cmd2.Cmd):
    prompt = 'uz> '
    intro = 'Welcome to the Ultrazohm shell. Type help or ? to list commands.\n'

    def __init__(self):
        super().__init__()
        self.uz = None
        self.connected = False
        self.loop = asyncio.new_event_loop()
        self.loop_thread = threading.Thread(target=self.loop.run_forever, daemon=True)
        self.loop_thread.start()

    def do_connect(self, arg):
        """connect [ip] [port] -- Connect to ultrazohm (ip/port optional)"""
        args = arg.split()
        ip = args[0] if len(args) > 0 else '127.0.0.1'
        port = int(args[1]) if len(args) > 1 else 1000
        self.uz = ultrazohm(ip, port)
        fut = asyncio.run_coroutine_threadsafe(self.uz.connect(), self.loop)
        fut.result()  # Wait for connection
        self.connected = True
        self.poutput(f"Connected to {ip}:{port}")

    def do_disconnect(self, arg):
        """disconnect -- Disconnect from ultrazohm"""
        if self.uz and self.connected:
            fut = asyncio.run_coroutine_threadsafe(self.uz.disconnect(), self.loop)
            fut.result()
            self.connected = False
            self.poutput("Disconnected.")
        else:
            self.poutput("Not connected.")

    def do_create_logfile_fast(self, arg):
        """create_logfile_fast [filename] -- Create fast logfile (filename optional)"""
        if self.uz:
            filename = arg.strip() if arg else None
            self.uz.create_logfile_fast(filename)
        else:
            self.poutput("Not connected.")

    def do_create_logfile_slow(self, arg):
        """create_logfile_slow [filename] -- Create slow logfile (filename optional)"""
        if self.uz:
            filename = arg.strip() if arg else None
            self.uz.create_logfile_slow(filename)
        else:
            self.poutput("Not connected.")

    def do_log_fast(self, arg):
        """log_fast [on/off] [filename] -- Enable/disable fast logging (filename optional)"""
        if self.uz:
            args = arg.split()
            enable = args[0].lower() in ("on", "true", "1", "yes") if args else True
            filename = args[1] if len(args) > 1 else None
            self.poutput(f"log_fast called with enable={enable}, filename={filename}")
            self.uz.log_fast(enable, filename)
        else:
            self.poutput("Not connected.")

    def do_log_slow(self, arg):
        """log_slow [on/off] [filename] -- Enable/disable slow logging (filename optional)"""
        if self.uz:
            args = arg.split()
            enable = args[0].lower() in ("on", "true", "1", "yes") if args else True
            filename = args[1] if len(args) > 1 else None
            self.poutput(f"log_slow called with enable={enable}, filename={filename}")
            self.uz.log_slow(enable, filename)
        else:
            self.poutput("Not connected.")

    def do_start_communication(self, arg):
        """start_communication [on/off] -- Start/stop communication"""
        if self.uz:
            args = arg.split()
            enable = args[0].lower() in ("on", "true", "1", "yes") if args else True
            self.poutput(f"start_communication called with enable={enable}")
            # Run start_communication in the background so cmd2 input is not blocked
            def run_bg():
                fut = asyncio.run_coroutine_threadsafe(self.uz.start_communication(enable), self.loop)
                try:
                    fut.result()  # Wait for scheduling, not for the task to finish
                except Exception as e:
                    self.poutput(f"Error in start_communication: {e}")
            threading.Thread(target=run_bg, daemon=True).start()
        else:
            self.poutput("Not connected.")

    def do_set_command(self, arg):
        """set_command <id> <value> -- Send command (id: int, value: float)"""
        if self.uz:
            args = arg.split()
            if len(args) < 2:
                self.poutput("Usage: set_command <id> <value>")
            else:
                try:
                    id_input = int(args[0])
                    value_input = float(args[1])
                    self.poutput(f"set_command called with id={id_input}, value={value_input}")
                    fut = asyncio.run_coroutine_threadsafe(self.uz.set_command(id_input, value_input), self.loop)
                    fut.result()
                except Exception as e:
                    self.poutput(f"Error: {e}")
        else:
            self.poutput("Not connected.")

    def do_set_command_skip_queue(self, arg):
        """set_command_skip_queue <id> <value> -- Send command and clear queue (id: int, value: float)"""
        if self.uz:
            args = arg.split()
            if len(args) < 2:
                self.poutput("Usage: set_command_skip_queue <id> <value>")
            else:
                try:
                    id_input = int(args[0])
                    value_input = float(args[1])
                    self.poutput(f"set_command_skip_queue called with id={id_input}, value={value_input}")
                    fut = asyncio.run_coroutine_threadsafe(self.uz.set_command_skip_queue(id_input, value_input), self.loop)
                    fut.result()
                except Exception as e:
                    self.poutput(f"Error: {e}")
        else:
            self.poutput("Not connected.")

    def do_get_scope_buffer_data(self, arg):
        """get_scope_buffer_data -- Print current scope buffer"""
        if self.uz:
            self.poutput("get_scope_buffer_data called")
            self.poutput(self.uz.get_scope_buffer_data())
        else:
            self.poutput("Not connected.")

    def do_exit(self, arg):
        """Exit the shell."""
        if self.uz and self.connected:
            fut = asyncio.run_coroutine_threadsafe(self.uz.disconnect(), self.loop)
            fut.result()
        self.loop.call_soon_threadsafe(self.loop.stop)
        self.poutput("Bye!")
        return True

    def do_EOF(self, arg):
        """Exit on Ctrl-D."""
        return self.do_exit(arg)

    def do_set_cmd_queue_size(self, arg):
        """set_cmd_queue_size <size> -- Set the command queue size"""
        if self.uz:
            try:
                size = int(arg.strip())
                self.uz.set_cmd_queue_size(size)
                self.poutput(f"set_cmd_queue_size called with size={size}")
            except Exception as e:
                self.poutput(f"Error: {e}")
        else:
            self.poutput("Not connected.")

    def do_get_cmd_queue_size(self, arg):
        """get_cmd_queue_size -- Get the command queue size"""
        if self.uz:
            size = self.uz.get_cmd_queue_size()
            self.poutput(f"cmd_queue_size: {size}")
        else:
            self.poutput("Not connected.")

    def do_set_from_ethernet_queue_size(self, arg):
        """set_from_ethernet_queue_size <size> -- Set the from_ethernet queue size"""
        if self.uz:
            try:
                size = int(arg.strip())
                self.uz.set_from_ethernet_queue_size(size)
                self.poutput(f"set_from_ethernet_queue_size called with size={size}")
            except Exception as e:
                self.poutput(f"Error: {e}")
        else:
            self.poutput("Not connected.")

    def do_get_from_ethernet_queue_size(self, arg):
        """get_from_ethernet_queue_size -- Get the from_ethernet queue size"""
        if self.uz:
            size = self.uz.get_from_ethernet_queue_size()
            self.poutput(f"from_ethernet_queue_size: {size}")
        else:
            self.poutput("Not connected.")

    def do_set_max_buffer_size(self, arg):
        """set_max_buffer_size <size> -- Set the max buffer size"""
        if self.uz:
            try:
                size = int(arg.strip())
                self.uz.set_max_buffer_size(size)
                self.poutput(f"set_max_buffer_size called with size={size}")
            except Exception as e:
                self.poutput(f"Error: {e}")
        else:
            self.poutput("Not connected.")

    def do_get_max_buffer_size(self, arg):
        """get_max_buffer_size -- Get the max buffer size"""
        if self.uz:
            size = self.uz.get_max_buffer_size()
            self.poutput(f"max_buffer_size: {size}")
        else:
            self.poutput("Not connected.")

if __name__ == '__main__':
    UltrazohmShell().cmdloop()
