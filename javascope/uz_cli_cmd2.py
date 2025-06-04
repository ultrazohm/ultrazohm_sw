import cmd2
from uz_class_threads import ultrazohm

class UltrazohmShell(cmd2.Cmd):
    prompt = 'uz> '
    intro = 'Welcome to the Ultrazohm shell. Type help or ? to list commands.\n'

    def __init__(self):
        super().__init__()
        self.uz = None
        self.connected = False

    def do_connect(self, arg):
        """connect [ip] [port] -- Connect to ultrazohm (ip/port optional)"""
        args = arg.split()
        ip = args[0] if len(args) > 0 else '127.0.0.1'
        port = int(args[1]) if len(args) > 1 else 1000
        self.uz = ultrazohm(ip, port)
        self.uz.connect()
        self.connected = True
        self.poutput(f"Connected to {ip}:{port}")

    def do_disconnect(self, arg):
        """disconnect -- Disconnect from ultrazohm"""
        if self.uz:
            self.uz.disconnect()
            self.uz = None
            self.connected = False
            self.poutput("Disconnected.")
        else:
            self.poutput("Not connected.")

    def do_start_communication(self, arg):
        """start_communication -- Start communication"""
        if self.uz:
            self.uz.start_communication(True)
            self.poutput("Communication started.")
        else:
            self.poutput("Not connected.")

    def do_stop_communication(self, arg):
        """stop_communication -- Stop communication"""
        if self.uz:
            self.uz.start_communication(False)
            self.poutput("Communication stopped.")
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
                    self.uz.set_command(id_input, value_input)
                    self.poutput(f"set_command called with id={id_input}, value={value_input}")
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
                    self.uz.set_command_skip_queue(id_input, value_input)
                    self.poutput(f"set_command_skip_queue called with id={id_input}, value={value_input}")
                except Exception as e:
                    self.poutput(f"Error: {e}")
        else:
            self.poutput("Not connected.")

    def do_create_logfile_fast(self, arg):
        """create_logfile_fast [filename] -- Create fast logfile (filename optional)"""
        if self.uz:
            filename = arg.strip() if arg.strip() else None
            self.uz.create_logfile_fast(filename)
            self.poutput(f"Fast logfile created: {self.uz.logfile_fast_name}")
        else:
            self.poutput("Not connected.")

    def do_create_logfile_slow(self, arg):
        """create_logfile_slow [filename] -- Create slow logfile (filename optional)"""
        if self.uz:
            filename = arg.strip() if arg.strip() else None
            self.uz.create_logfile_slow(filename)
            self.poutput(f"Slow logfile created: {self.uz.logfile_slow_name}")
        else:
            self.poutput("Not connected.")

    def do_log_fast(self, arg):
        """log_fast [on/off] [filename] -- Enable/disable fast logging (filename optional)"""
        if self.uz:
            args = arg.split()
            enable = args[0].lower() == 'on' if args else False
            filename = args[1] if len(args) > 1 else None
            self.uz.log_fast(enable, filename)
            self.poutput(f"Fast logging {'enabled' if enable else 'disabled'}.")
        else:
            self.poutput("Not connected.")

    def do_log_slow(self, arg):
        """log_slow [on/off] [filename] -- Enable/disable slow logging (filename optional)"""
        if self.uz:
            args = arg.split()
            enable = args[0].lower() == 'on' if args else False
            filename = args[1] if len(args) > 1 else None
            self.uz.log_slow(enable, filename)
            self.poutput(f"Slow logging {'enabled' if enable else 'disabled'}.")
        else:
            self.poutput("Not connected.")

    def do_get_scope_buffer_data(self, arg):
        """get_scope_buffer_data -- Print current scope buffer"""
        if self.uz:
            data = self.uz.get_scope_buffer_data()
            self.poutput(f"Scope buffer data: {data}")
        else:
            self.poutput("Not connected.")

if __name__ == '__main__':
    UltrazohmShell().cmdloop()
