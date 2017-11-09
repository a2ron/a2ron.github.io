./build-for-tv-box.sh http-terminal/server.go
tar -cvf server.tar server
#scp server.tar <user>@<host>:/sdcard/lab/
rm server server.tar
ssh <user>@<host>
########################################################################################################################
export TAR_PATH="/sdcard/lab/server.tar"
export DEPLOY_PATH="/data/local"

su -c "
tar xf $TAR_PATH -C $DEPLOY_PATH ; \
rm $TAR_PATH; \
chmod u+x $DEPLOY_PATH/server ; \
certsPath=$DEPLOY_PATH $DEPLOY_PATH/server"