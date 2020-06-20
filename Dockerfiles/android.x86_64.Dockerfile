FROM a12e/docker-qt:5.13-android_x86_64

RUN git clone https://github.com/a-khakimov/SmartTap.git; \
    cd SmartTap/Game; \
    mkdir build; \
    cd build; \
    qmake -r .. ANDROID_EXTRA_LIBS+=$ANDROID_DEV/lib/libcrypto.so \
                ANDROID_EXTRA_LIBS+=$ANDROID_DEV/lib/libssl.so; \
    make; \
    make install INSTALL_ROOT=../dist; \
    cd ..; \
    androiddeployqt --input build/android-libSmartTap.so-deployment-settings.json \
                    --output dist/ --aab --deployment bundled --gradle --release; \
    cp android/AndroidManifest.x86_64.xml dist/AndroidManifest.xml; \
    ./dist/gradlew build
