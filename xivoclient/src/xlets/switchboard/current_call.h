/* XiVO Client
 * Copyright (C) 2012-2014 Avencall
 *
 * This file is part of XiVO Client.
 *
 * XiVO Client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version, with a Section 7 Additional
 * Permission as follows:
 *   This notice constitutes a grant of such permission as is necessary
 *   to combine or link this software, or a modified version of it, with
 *   the OpenSSL project's "OpenSSL" library, or a derivative work of it,
 *   and to copy, modify, and distribute the resulting work. This is an
 *   extension of the special permission given by Trolltech to link the
 *   Qt code with the OpenSSL library (see
 *   <http://doc.trolltech.com/4.4/gpl.html>). The OpenSSL library is
 *   licensed under a dual license: the OpenSSL License and the original
 *   SSLeay license.
 *
 * XiVO Client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XiVO Client.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CURRENT_CALL_H__
#define __CURRENT_CALL_H__

#include <ipbxlistener.h>
#include <QObject>

class QWidget;
class QPushButton;

namespace Ui {
    class CurrentCallWidget;
}

enum RequestedAction {
    ATTENDED_TRANSFER,
    CALL,
    DIRECT_TRANSFER
};


class CurrentCall: public QObject, public IPBXListener
{
    Q_OBJECT

    public:
        CurrentCall(QObject *parent=NULL);
        ~CurrentCall();
        void setParentWidget(QWidget *parent);
        virtual void parseCommand(const QVariantMap &command);
        void noticeIncoming(bool);
        void updateCurrentCall(const QVariantList &calls, bool has_incoming);
    public slots:
        void answer();
        void attendedTransfer();
        void call();
        void directTransfer();
        void completeTransfer();
        void cancelTransfer();
        void hangup();
        void hold();
    private slots:
        void updateCallInfo();
        void numberSelected(const QString &number);
        void noNumberSelected();
    private:
        void clear();
        void updateCallerID(const QString &name, const QString &number);
        void updateCall(const QVariantList &calls);
        void parseAttendedTransferAnswered(const QVariantMap &message);
        bool hasCurrentCall() const;

	void callingMode();
        void readyToAnswerMode(bool has_incoming);
        void noCallsMode();
        void ringingMode();
        void answeringMode();
        void transferRingingMode();
        void transferAnsweredMode();
        void resetButtons();

        void setButton(QPushButton*, const QString &, const QKeySequence &, const char *);
        void setButton(QPushButton*, const QKeySequence &, const char *);
        void setButton(QPushButton*, const char *);

        void setAnswerButton();
        void setAttendedTransferButton();
        void setCallButton();
        void setDirectTransferButton();
        void setCompleteTransferButton();
        void setHoldButton();
        void setHangupButton();
        void setCancelTransferButton();

        Ui::CurrentCallWidget *m_current_call_widget;
        double m_call_start;
        QString m_caller_id;

        QString m_attended_transfer_label;
        QString m_call_label;
        QString m_complete_transfer_label;
        QString m_hangup_label;
        QString m_cancel_transfer_label;
        static QKeySequence direct_transfer_key;
        static QKeySequence call_key;
        static QKeySequence attended_transfer_key;
        static QKeySequence hangup_key;

        RequestedAction m_requested_action;
};

#endif /* __CURRENT_CALL_H__ */
