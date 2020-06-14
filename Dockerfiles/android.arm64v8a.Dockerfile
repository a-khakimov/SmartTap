FROM a12e/docker-qt:5.13-android_arm64_v8a

RUN git clone https://github.com/a-khakimov/SmartTap.git; \
cd SmartTap/Game; \
mkdir build; \
cd build; \
qmake -r .. ANDROID_EXTRA_LIBS+=$ANDROID_DEV/lib/libcrypto.so ANDROID_EXTRA_LIBS+=$ANDROID_DEV/lib/libssl.so; \
make; \
make install INSTALL_ROOT=../dist; \
cd ..; \
androiddeployqt --input build/android-libSmartTap.so-deployment-settings.json --output dist/ --aab --deployment bundled --gradle --release; \
sudo apt install zipalign -y; \
zipalign -f -v 4 dist/build/outputs/apk/release/dist-release-unsigned.apk smarttap.zipalign.apk
