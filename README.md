# App2Systemd

# Compile
```
$ make
$ sudo make install
```

# Install service
```
$ sudo systemctl enable vaca.service
Created symlink from /etc/systemd/system/multi-user.target.wants/vaca.service to /etc/systemd/system/vaca.service.

$ sudo systemctl start vaca.service
```

Check status of service:
```
$ sudo systemctl status vaca
● vaca.service - Application Vaca CPP
   Loaded: loaded (/etc/systemd/system/vaca.service; enabled; vendor preset: enabled)
   Active: active (running) since Ter 2019-01-08 13:44:49 -02; 2s ago
 Main PID: 16788 (vaca)
    Tasks: 1
   Memory: 180.0K
      CPU: 3ms
   CGroup: /system.slice/vaca.service
           └─16788 /opt/app/vaca

Jan 08 13:44:49  systemd[1]: Started Application Vaca CPP.
Jan 08 13:44:49  vaca[16788]: PID: 16788
```

Stopped service:
```
$ cat /tmp/output.log 
Go Loop
.........
$ sudo systemctl stop vaca
$ cat /tmp/output.log 
Go Loop
.....................
*******************
* SIGQUIT received *
*******************

Muhhh, by...

```

# Send kill QUIT
```
$ kill -QUIT $(pgrep vaca)
```

# Log file
```
$ cat /tmp/output.log
Go Loop
..................
*******************
* SIGINT received *
*******************
Ctrl+C disabled...............
*******************
* SIGHUP received *
*******************
Ow, warning the terminal died but I'm alive.........................
*******************
* SIGQUIT received *
*******************

Muhhh, by...

```

# Remove and clean environment
```
$ sudo systemctl stop vaca
$ sudo systemctl disable vaca
Removed symlink /etc/systemd/system/multi-user.target.wants/vaca.service.
$ sudo make uninstall
rm -f /opt/app/vaca
rm -f /etc/systemd/system/vaca.service
```

***

Contact
-------

cleitonrbueno at gmail.com

