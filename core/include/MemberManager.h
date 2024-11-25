#pragma once

#include <QList>
#include <QSharedPointer>
#include <QSqlDatabase>

class MemberManager : public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<MemberManager> instance(QSharedPointer<QSqlDatabase> database, QObject* parent);
	QList<QString> getMembers() const;
	void addMember(const QString& member);
	void removeMember(const QString& member);
	void updateMember(const QString& oldMember, const QString& newMember);

signals:
	void memberAdded(QString member);
	void memberRemoved(QString member);
	void memberUpdated(QString oldMember, QString newMember);

private:
	MemberManager(QSharedPointer<QSqlDatabase> database, QObject *parent);
	MemberManager(const MemberManager& manager);
	MemberManager& operator=(const MemberManager & manager);


private:
	QList<QString> mMembers;
	QSharedPointer<QSqlDatabase> mDatabasePtr;
	QString mMemberTableName;
};
