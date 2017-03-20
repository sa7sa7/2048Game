#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <game2048.h>
#include <time.h>
#include <QtQml>
#include <test.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Game2048 exec;
    //Game_AI kharya;
    //kharya.set_exec_copie(&exec);
    //Q_DECLARE_METATYPE(exec);
    /*Test test;
    test.init();*/
    srand(time(NULL));
    exec.init_grid();
    //exec.set_response(-1);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("grid",(&exec));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
