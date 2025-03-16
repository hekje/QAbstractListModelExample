/*****************************************************************************
*
* Copyright 2025 - Heʞ
*
*****************************************************************************/

#pragma once

#include <QAbstractListModel>
#include <QMap>
#include <QPointer>
#include <QObject>
#include <QQmlEngine>


class QObjectListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit QObjectListModel(QObject* parent = nullptr)
        : QAbstractListModel(parent) {}

    ~QObjectListModel() {
        qDebug() << "~QObjectListModel - Enter destructor";
        m_objectsMap.clear(); // QPointer ensures objects are deleted if parented
    }

    enum ObjectRoles {
        IdRole = Qt::UserRole + 1,
        ObjectRole
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return m_objectsMap.size();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (!index.isValid() || index.row() >= m_objectsMap.size())
            return QVariant();

        auto it = m_objectsMap.begin();
        std::advance(it, index.row());

        switch (role) {
        case IdRole:
            return it.key();
        case ObjectRole:
            return QVariant::fromValue(it.value().data());
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override {
        return {{IdRole, "id"}, {ObjectRole, "object"}};
    }

    bool containsID(uint32_t id) const {
        return m_objectsMap.contains(id);
    }

    void addObject(uint32_t id, QObject* object) {
        if (m_objectsMap.contains(id)) return;
        beginInsertRows(QModelIndex(), m_objectsMap.size(), m_objectsMap.size());
        m_objectsMap.insert(id, object);
        endInsertRows();
    }

    void removeObject(uint32_t id) {
        auto it = m_objectsMap.find(id);
        if (it != m_objectsMap.end()) {
            int row = std::distance(m_objectsMap.begin(), it);
            beginRemoveRows(QModelIndex(), row, row);
            m_objectsMap.erase(it);  // QPointer auto-clears if object is deleted
            endRemoveRows();
        }
    }

    QObject* getObjectByID(uint32_t id) const {
        return m_objectsMap.value(id, nullptr);
    }

private:
    QMap<uint32_t, QPointer<QObject>> m_objectsMap;
};






