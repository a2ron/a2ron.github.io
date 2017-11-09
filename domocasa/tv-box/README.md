# TV-BOX

As you probably already know from [my article in CodedPoetry ;-)](http://codedpoetry.com/tvbox-hacks/), you can have full control of your tv-box, launching Linux commands through SSH directly.

You can open an app this way:
```
am start org.xbmc.kodi/.Splash 
```
You can stop an app this way:
```
pkill -9 kodi
```
But, what about to do it through HTTP request and then, to be able to integrate with other pieces via rules, automatism, etc?
Let's build the TV-BOX API.

Golang servers to launch commands on demand by a webserver in a TV Box.
2 approaches:
- [google-dialog-flow-worker](google-dialog-flow-worker): example of integration with **Google Dialog Flow**
- [http-terminal](http-terminal): web server to send super user commands through HTTP GET query parameters

## TV Box requirements

- Android, Linux Kernel, ARM
- SSH Server

## Build, Setup and Launch
_see [deploy.example.md](deploy.example.md)_

* **1**.- To build the binary release

```
./build-for-tv-box.sh <server-file.go>
```
* **2**.- Compress and pack your release

```bash
tar -cvf server.tar <compiled-server-file> [assets] ...
```
* **3**.- Copy the release to the TV Box

```
scp server.tar <user>@<host>:<destination_path>
```

* **4**.-  Log in the TV Box via SSH

```
ssh <user>@<host>
```

* **5**.- Setup and launch the server (in the TV Box)

```
export TAR_PATH="<destination_path>/server.tar"
export DEPLOY_PATH="<path_with_execution_permissions>"

su -c "
tar xf $TAR_PATH -C $DEPLOY_PATH ; \
rm $TAR_PATH; \
chmod u+x $DEPLOY_PATH/server ; \
certsPath=$DEPLOY_PATH $DEPLOY_PATH/server"
```

* **6**.- To launch on init (in the TV Box)

```
SERVER_BIN=\"/data/local/server\" ; \
LOG_FILE=\"/data/local/server.log\" ; \
su -c "
    mount -o rw,remount,rw /system
    echo \"
        # launch server on init and log
        date >> $LOG_FILE
        echo 'Launching server' >> $LOG_FILE
        $SERVER_BIN >> $LOG_FILE
    \" >>  /system/bin/preinstall.sh
"
```