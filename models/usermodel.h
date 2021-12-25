#ifndef USERMODEL_H
#define USERMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <users.h>

class RepoDB;

class UserModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum UserRoles {
        IDRole = Qt::UserRole + 1,
        UsernameRole,
        PasswordRole,
        TypeRole,
        WorkerIDRole
    };
    Q_ENUM(UserRoles)

    explicit UserModel(RepoDB* repodb, QObject *parent = nullptr);

    Q_INVOKABLE void loadUsers();
    Q_INVOKABLE void clearModel();
    Q_INVOKABLE void reloadUsers();

    Q_INVOKABLE void deleteUser(const int& id);

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const override;
    virtual Q_INVOKABLE Qt::ItemFlags flags(const QModelIndex &index)const override;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole)override;
    virtual Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex()) override;


protected:
    virtual QHash<int, QByteArray> roleNames() const override;

signals:
    void rowCountChanged(int count);

private:

    QList<Users> m_data;
    RepoDB* m_db;

};

#endif // USERMODEL_H
