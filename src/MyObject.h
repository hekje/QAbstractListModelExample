#include <QObject>
#include <QRandomGenerator>
#include <QDebug>
#include "QObjectListModel.h"

// Global constants
constexpr int MAX_X = 800;
constexpr int MAX_Y = 800;

class MyObject : public ISystemID {
    Q_OBJECT
    Q_PROPERTY(int x READ getX CONSTANT)
    Q_PROPERTY(int y READ getY CONSTANT)

public:
    explicit MyObject(uint32_t id, QObject* parent = nullptr)
        : ISystemID(parent)
        , m_id(id)
        , m_x(QRandomGenerator::global()->bounded(MAX_X + 1))
        , m_y(QRandomGenerator::global()->bounded(MAX_Y + 1)) {

        qDebug() << "MyObject - Enter constructor: m_x:" << m_x << "m_y:" << m_y;
    }

    ~MyObject() {
        qDebug() << "~MyObject - Enter destructor" ;
    }

    int getX() const { return m_x; }
    int getY() const { return m_y; }

private:
    uint32_t m_id;
    int m_x;
    int m_y;
};
