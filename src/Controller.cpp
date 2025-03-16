#include "Controller.h"
#include <QDebug>
#include <QQmlContext>
#include "MyObject.h"


Controller::Controller(QQmlApplicationEngine *engine, QObject *parent)
    : QObject(parent), m_engine(engine)
    , m_objModel(new QObjectListModel(this))
{
    // Expose the Controller instance **before** loading QML
    m_engine->rootContext()->setContextProperty("controller", this);

    // Now load QML (AFTER setting context properties)
    m_engine->load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    // Check if the QML file loaded correctly
    if (m_engine->rootObjects().isEmpty()) {
        qCritical() << "Failed to load main.qml.";
        return;
    }

    // Get the root object of the QML application
    QObject *rootObject = m_engine->rootObjects().first();

    // Connect QML signal to C++ sloVehiclet
    if (rootObject) {
        connect(rootObject, SIGNAL(buttonPressed()), this, SLOT(onButtonClicked()));
    } else {
        qCritical() << "Root object is null.";
    }
}



Controller::~Controller()
{
    // Destructor definition (even if empty)
    // This allows the MOC to handle the class correctly.
}

QString Controller::message() const
{
    return m_message;
}

void Controller::setMessage(const QString &message)
{
    if (m_message != message) {
        m_message = message;

        qDebug() << "Controller::setMessage - emit messageChanged signal";
        emit messageChanged();  // Notify QML about the change
    }
}

void Controller::onButtonClicked()
{
    qDebug() << "Button clicked! Signal received in Controller.";

    int size = m_objModel ? m_objModel->rowCount() : 0;
    qDebug() << "Object list size:" << size;

    // Create and add a new MyObject instance
    QPointer<MyObject> obj = new MyObject(size + 1, this);
    addObject(size + 1, obj);

    setMessage("Button clicked!");  // Update the message property
}
