FROM a12e/docker-qt:5.13-android_arm64_v8a

RUN git clone https://github.com/a-khakimov/SmartTap.git \
    cd SmartTap \
    mkdir build \
    cd build/   \
    make        \
    qmake -r .. ANDROID_EXTRA_LIBS+=$ANDROID_DEV/lib/libcrypto.so ANDROID_EXTRA_LIBS+=$ANDROID_DEV/lib/libssl.so \
    make install INSTALL_ROOT=../dist \
    cd ..       \
    androiddeployqt --input build/android-libSmartTap.so-deployment-settings.json \
                    --output dist/ --deployment bundled --gradle --release
