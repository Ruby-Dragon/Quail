# Quail
Simple GUI wrapper for Tailscale written in C++ with QT

### Commands:
- Up
- Down
- Logout
- IP
- Status
- Exit Node

Click on the corresponding button to execute the command. Exit Node is a text box that you put the exit node name/IP into. The exit node entered will automatically be used
when the up button is pressed.

### Todo list:
- Fix output from tailscale CLI
- Add checking for exit codes from tailscale (can't find documentation)
- add timeout for tailscale up
- Add documentation
- Create pkgbuild
- Possibly add more features once current state is stable
