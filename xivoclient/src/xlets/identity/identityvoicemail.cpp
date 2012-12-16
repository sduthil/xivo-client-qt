/* XiVO Client
 * Copyright (C) 2007-2011, Avencall
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

/* $Revision$
 * $Date$
 */

#include <QGridLayout>
#include <QPixmap>
#include <QLabel>
#include <QToolTip>
#include <QDebug>
#include "baseengine.h"
#include "identityvoicemail.h"
#include "userinfo.h"
#include "voicemailinfo.h"

/*! \brief Constructor
 */
IdentityVoiceMail::IdentityVoiceMail(QWidget * parent)
    : QWidget(parent), m_initialized(false), m_voicemailinfo(NULL)
{
    setObjectName("identityvoicemail");
    m_layout = new QGridLayout( this );

    m_iconButton = new QPushButton(this);
    m_iconButton->setFocusPolicy(Qt::NoFocus);
    m_iconButton->setToolTip(tr("call your voicemail"));
    icon_no_message = QPixmap(":/images/identity/internet-mail.png");
    icon_new_message = QPixmap(":/images/identity/mail-message-new.png");
    m_iconButton->setObjectName("voicemail_button");
    m_iconButton->setIcon(icon_no_message);
    m_iconButton->setFlat(true);
    m_iconButton->setIconSize(icon_no_message.size());
    m_iconButton->setEnabled(false);

    QGridLayout *text_layout = new QGridLayout(m_iconButton);

    newMessageIndicator = new QPushButton(this);
    newMessageIndicator->setText("");
    newMessageIndicator->setStyleSheet("QPushButton {color : white; background-color: #F37021;border-radius: 8px;}");
    newMessageIndicator->setEnabled(false);
    newMessageIndicator->setFixedWidth(20);

    oldMessageIndicator = new QPushButton(this);
    oldMessageIndicator->setText("");
    oldMessageIndicator->setStyleSheet("QPushButton {color : white; background-color: darkgrey;border-radius: 8px;}");
    oldMessageIndicator->setEnabled(false);
    oldMessageIndicator->setVisible(true);
    oldMessageIndicator->setFixedWidth(20);

    text_layout->addWidget(oldMessageIndicator,0,0);
    text_layout->addWidget(newMessageIndicator,1,1);
    m_layout->addWidget(m_iconButton, 0, 0, 3, 1, Qt::AlignHCenter|Qt::AlignTop);

    connect(m_iconButton, SIGNAL(clicked()), this, SLOT(callVoiceMail()));

    m_name = new QLabel(this);
    m_name->setObjectName("voicemail_num");
    m_layout->addWidget(m_name, 0, 1, Qt::AlignLeft|Qt::AlignVCenter);

}

void IdentityVoiceMail::setVoiceMailId(const QString & xvoicemailid)
{
    m_xvoicemailid = xvoicemailid;
    m_voicemailinfo = b_engine->voicemail(xvoicemailid);
}

/*! \brief update voicemail box name.
 */
void IdentityVoiceMail::svcSummary(QVariantMap &svcstatus, const UserInfo * ui)
{
    bool has_phone = (ui && ui->phonelist().size());
    m_iconButton->setEnabled(has_phone);
    if (! m_voicemailinfo && ui) {
        setVoiceMailId(ui->xvoicemailid());
        updateVoiceMailStatus(m_xvoicemailid);
    }
    if (m_voicemailinfo == NULL)
        return;
    if(svcstatus["enablevoicemail"].toBool()) {
        m_name->setText(tr("<b>VoiceMailBox %1</b>").arg(m_voicemailinfo->mailbox()));
        m_name->setToolTip(tr("VoiceMail activated on %1").arg(m_voicemailinfo->mailbox()));
    } else {
        m_name->setText(tr("VoiceMailBox %1").arg(m_voicemailinfo->mailbox()));
        m_name->setToolTip(tr("VoiceMail not activated on %1").arg(m_voicemailinfo->mailbox()));
    }
}

/*! \brief call voicemail on click
 */
void IdentityVoiceMail::callVoiceMail()
{
    if (m_voicemailinfo)
        b_engine->actionCall("dial", "",
                             QString("voicemail:%1").arg(m_voicemailinfo->xid()));
}

/*! \brief Send an event to get complete voicemail status */
void IdentityVoiceMail::queryVM()
{
    if (! m_initialized && m_voicemailinfo) {
        QVariantMap command;
        command["command"] = "mailboxcount";
        command["mailbox"] = m_voicemailinfo->mailbox();
        command["context"] = m_voicemailinfo->context();
        b_engine->ipbxCommand(command);
        m_initialized = true;
    }
}

void IdentityVoiceMail::updateVoiceMailConfig(const QString & xvoicemailid)
{
    if (xvoicemailid != m_xvoicemailid)
        return;
    m_voicemailinfo = b_engine->voicemail(xvoicemailid);
    if (m_voicemailinfo == NULL)
        return;
    queryVM();
    m_name->setText(tr("VoiceMailBox %1").arg(m_voicemailinfo->mailbox()));
}

void IdentityVoiceMail::updateVoiceMailStatus(const QString & xvoicemailid)
{
    if (xvoicemailid != m_xvoicemailid)
        return;
    if (m_voicemailinfo == NULL)
        return;
    updateMessageIndicators(m_voicemailinfo->newMessages(),m_voicemailinfo->oldMessages());
    updateMessageIndicators(3,6);
}

void IdentityVoiceMail::updateMessageIndicators(const int nbOfNewMessages, const int nbOfOldMessages)
{
     newMessageIndicator->setText(QString::number(nbOfNewMessages));
     oldMessageIndicator->setText(QString::number(nbOfOldMessages));
     if (nbOfNewMessages == 0) {
             m_iconButton->setIcon(icon_no_message);
     }
     else {
             m_iconButton->setIcon(icon_new_message);
     }
 }

