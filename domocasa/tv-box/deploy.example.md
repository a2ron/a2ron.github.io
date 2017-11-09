In your development host:

```
./build-for-tv-box.sh http-terminal/server.go
tar -cvf server.tar server
scp server.tar <user>@<host>:/sdcard/lab/
ssh <user>@<host>
```
In your tv-box (through ssh):

```
export TAR_PATH="/sdcard/lab/server.tar"
export DEPLOY_PATH="/data/local"

su -c "
tar xf $TAR_PATH -C $DEPLOY_PATH ; \
rm $TAR_PATH; \
chmod u+x $DEPLOY_PATH/server ; \
certsPath=$DEPLOY_PATH $DEPLOY_PATH/server"
```