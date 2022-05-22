/**
                                    _
                              _ooOoo_
                             o8888888o
                             88" . "88
                             (| -_- |)
                             O\  =  /O
                          ____/`---'\____
                        .'  \\|     |//  `.
                       /  \\|||  :  |||//  \
                      /  _||||| -:- |||||_  \
                      |   | \\\  -  /'| |   |
                      | \_|  `\`---'//  |_/ |
                      \  .-\__ `-. -'__/-.  /
                    ___`. .'  /--.--\  `. .'___
                 ."" '<  `.___\_<|>_/___.' _> \"".
                | | :  `- \`. ;`. _/; .'/ /  .' ; |
                \  \ `-.   \_\_`. _.'_/_/  -' _.' /
  ================-.`___`-.__\ \___  /__.-'_.'_.-'================
                              `=--=-'

                   佛祖保佑    永无BUG    永不宕机
 *
 */
//#define NO_X_TEST //解开注释以开启无界面测试
#ifndef NO_X_TEST
#include "encloudcontroller.h"
#include <QApplication>
#include <QIcon>
#include <QThreadPool>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName("EnCloud");
    QApplication::setWindowIcon(QIcon(":/icons/idea.png"));

    EncloudController controller;
    controller.run();

    //进入应用消息循环
    return app.exec();
}
#else
#include "test/qtapitest.h"
#include "test/opensslapitest.h"
#include "test/mytest.h"
#include <QApplication>
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    //Qt API test
//    network_test();
//    json_test();
    MD5_test();

    //OpenSSL API test
//    AES_TEST();
//    RSA_TEST();

    //My API test
//    networkmgr_test();
//    cryptographymanager_test1();
//    cryptographymanager_test2();
//    base64Test();
//    paddingTest();
//    mimeTest();
//    mapTest();
//    variantTest();
//    qbuffTest();
//    testED();
//    downloadTest();
    return app.exec();
}
#endif
