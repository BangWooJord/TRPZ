#include "usermodel.h"
#include "../repos/repodb.h"
#include "../repos/userrepo.h"
#include "../repos/workerrepo.h"
#include "worker.h"
#include "users.h"
#include <QVector>
#include <QDebug>

UserModel::UserModel(RepoDB* repodb, QObject *parent) :
    QAbstractListModel(parent), m_db(repodb)
{

}

void UserModel::loadUsers()
{
    const auto users = QVector<Users>::fromStdVector(
        m_db->userRepo()->getAll());
    beginInsertRows(QModelIndex(), m_data.count(), m_data.count() + users.size() - 1);
    m_data = QList<Users>::fromVector(users);
    endInsertRows();
}

void UserModel::clearModel()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

void UserModel::reloadUsers()
{
    clearModel();
    loadUsers();
}

void UserModel::deleteUser(const int& id)
{
    m_db->workerRepo()->Delete(m_db->userRepo()->get(id)->getWorkerID());
    m_db->userRepo()->Delete(id);
}

QHash<int, QByteArray> UserModel::roleNames() const
{
    return {{IDRole, "userid"},
            {UsernameRole, "username"},
            {PasswordRole, "password"},
            {TypeRole, "type"},
            {WorkerIDRole, "workerid"}};
}


// Subclassing implementation
int UserModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

QVariant UserModel::data(const QModelIndex & index, int role) const
{
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const auto &item = m_data.at(index.row());

    switch(role){
    case IDRole:
        return item.getID();
    case UsernameRole:
        return item.getUsername();
    case PasswordRole:
        return item.getPassword();
    case TypeRole:
        return item.getUserType();
    case WorkerIDRole:
        return item.getWorkerID();
    }
    return {};
}

Qt::ItemFlags UserModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool UserModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;

    auto& item = m_data[index.row()];

    switch (role){
    case UsernameRole:{
        item.setUsername(value.value<QString>());
    }
    case PasswordRole:{
        item.setPassword(value.value<QString>());
    }
    case TypeRole:{
        item.setUserType(value.value<uint>());
    }
    case WorkerIDRole:{
        item.setWorkerID(value.value<uint>());
    }
    }

    emit dataChanged(index, index, { role });
    return true;
}

bool UserModel::removeRows(int row, int count, const QModelIndex & parent)
{
    Q_UNUSED(count);
    Q_UNUSED(parent);
    if ((row < 0) || (row >= rowCount())) return false;
    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
    emit rowCountChanged(m_data.count());
    return true;
}
