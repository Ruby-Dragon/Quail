# Quail

###### GNU Public Licence v3, 2022, Ruby-Dragon

Simple GUI wrapper for Tailscale written in C++ with QT

### Building

```
# git clone https://github.com/Ruby-Dragon/Quail
# cd Quail
# cd Quail #subfolder of Quail
# cmake
# make
# quail
```

### Usage:
- Up, runs tailscale up and connects your device to your tailnet (gives a login link if not logged in)
- Down, runs tailscale down and stops tailscale
- Logout, runs tailscale logout and logs you out of your tailnet
- IP, runs tailscale ip and gives you your tailscale IP address
- Status, gets the status of your tailnet
- Exit Node, input is used as the name or IP of the exit node you want to use

Click on the corresponding button to execute the command. Exit Node is a text box that you put the exit node name/IP into. The exit node entered will automatically be used
when the up button is pressed.

### Todo list:
- Add documentation
- Fix translation loading
- Create AUR package
- Possibly add more features once current state is stable

## Licence

This software uses the GPL licence. Read the terms before using the source code.

###### ALL DERIVATIVE WORKS MUST BE GPL v3 LICENCED AS WELL, AND MUST KEEP ALL COPYRIGHT NOTICES IN CODE. See the LICENCE for more information.
