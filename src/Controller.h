#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "QObjectListModel.h"


class Controller : public QObject
{
    Q_OBJECT  // This macro enables meta-object features like signals and slots
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(QObjectListModel* objModel READ objModel CONSTANT)

public:
    explicit Controller(QQmlApplicationEngine *engine, QObject *parent = nullptr);
    ~Controller();  // Destructor declaration

    QString message() const;
    void setMessage(const QString &message);

    QObjectListModel* objModel() const { return m_objModel; }

    void addObject(uint32_t id, ISystemID* obj) {
        if (!obj) {
            qDebug() << "addObject - Invalid object pointer!";
            return;
        }

        if (m_objModel->containsID(id)) {
            qDebug() << "addObject - Object with ID" << id << "already exists.";
            return;
        }

        m_objModel->addObject(QPointer< ISystemID >(obj));
    }

    void removeObject(uint32_t id) {
        if (!m_objModel->containsID(id)) {
            qDebug() << "removeObject - Object with ID" << id << "does not exist.";
            return;
        }

        m_objModel->removeObject(id);
    }

signals:
    void messageChanged();

public slots:
    void onButtonClicked();  // Slot to handle button click

private:
    QQmlApplicationEngine *m_engine; // Engine reference
    QString m_message;

    QPointer<QObjectListModel> m_objModel; 
};

#endif // CONTROLLER_H
