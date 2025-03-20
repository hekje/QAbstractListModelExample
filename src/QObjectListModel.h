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


class ISystemID : public QObject {
    Q_OBJECT
    Q_PROPERTY( uint32_t systemID READ systemID WRITE setSystemID NOTIFY systemIDChanged )
public:
    explicit ISystemID( QObject *parent = nullptr )
        : QObject( parent ) {}
    virtual ~ISystemID() = default; // Virtual destructor to ensure proper cleanup

    // Getter
    uint32_t systemID() const { return m_systemID; }

    // Setter
    void setSystemID( uint32_t id ) {
        if ( m_systemID != id ) {
            m_systemID = id;
            emit systemIDChanged();
        }
    }

signals:
    void systemIDChanged();

protected:
    uint32_t m_systemID; // Protected so derived classes can access it
};

class QObjectListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit QObjectListModel( QObject *parent = nullptr )
        : QAbstractListModel( parent ) {}

    ~QObjectListModel() {
        qDebug() << "~QObjectListModel - Enter destructor";
        m_objectsList.clear(); // QPointer ensures objects are deleted if parented
    }

    enum ObjectRoles { IdRole = Qt::UserRole + 1, ObjectRole };

    int rowCount( const QModelIndex &parent = QModelIndex() ) const override {
        Q_UNUSED( parent )
        return m_objectsList.size();
    }

    QVariant data( const QModelIndex &index, int role ) const override {
        if ( !index.isValid() || index.row() >= m_objectsList.size() )
            return QVariant();

        auto obj = m_objectsList.at( index.row() );
        switch ( role ) {
        case IdRole:
            return obj->systemID(); // Return systemID of the ISystemID object
        case ObjectRole:
            return QVariant::fromValue( obj.data() ); // Return the QObject pointer itself
        }
        return QVariant();
    }

    QHash< int, QByteArray > roleNames() const override { return { { IdRole, "id" }, { ObjectRole, "object" } }; }

    bool containsID( uint32_t id ) const {
        for ( const auto &object : m_objectsList ) {
            if ( object && object->systemID() == id )
                return true;
        }
        return false;
    }

    void addObject( ISystemID *object ) {
        if ( !object )
            return;

        beginInsertRows( QModelIndex(), m_objectsList.size(), m_objectsList.size() );
        m_objectsList.append( QPointer< ISystemID >( object ) );
        endInsertRows();
    }

    void removeObject( uint32_t id ) {
        for ( int i = 0; i < m_objectsList.size(); ++i ) {
            if ( m_objectsList[ i ] && m_objectsList[ i ]->systemID() == id ) {
                beginRemoveRows( QModelIndex(), i, i );
                m_objectsList.removeAt( i );
                endRemoveRows();
                return; // Stop after removing the first match
            }
        }
    }

    void removeObject( ISystemID *object ) {
        auto it =
            std::find_if( m_objectsList.begin(), m_objectsList.end(), [ object ]( const QPointer< ISystemID > &ptr ) {
                return ptr == object;
            } );

        if ( it != m_objectsList.end() ) {
            int row = std::distance( m_objectsList.begin(), it );
            beginRemoveRows( QModelIndex(), row, row );
            m_objectsList.erase( it );
            endRemoveRows();
        }
    }

    ISystemID *getObjectByID( uint32_t id ) const {
        for ( const auto &obj : m_objectsList ) {
            if ( obj && obj->systemID() == id ) {
                return obj;
            }
        }
        return nullptr;
    }

private:
    QList< QPointer< ISystemID > > m_objectsList;
};
