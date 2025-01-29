#pragma once

#include <QList>
#include <QSharedPointer>
#include <QSqlDatabase>

#include <Member.h>

class MemberManager : public QObject
{
	Q_OBJECT

public:
    MemberManager(QObject* parent = nullptr);
	QList<Member> getMembers() const;
	void addMember(Member member);
	void removeMember(Member member);
	void updateMember(Member member);

    Member getMemberByFullName(const QString& name);

signals:
	void memberAdded(Member member);
	void memberRemoved(Member member);
	void memberUpdated(Member member);

private:
	QList<Member> mMembers;
	QString mMemberTableName;
};
