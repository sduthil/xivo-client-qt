/* XiVO Client
 * Copyright (C) 2007-2014 Avencall
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

#ifndef __CONTACTDIALOG_H__
#define __CONTACTDIALOG_H__

#include <QDialog>
#include <QLineEdit>

/*! \brief dialog for creating/editing a new personnal contact
 *
 */
class ContactDialog : public QDialog
{
    Q_OBJECT

    public:
        ContactDialog(QWidget *parent=0);
        QString firstname() const { return m_firstname?m_firstname->text():QString(); };
        QString lastname() const { return m_lastname?m_lastname->text():QString(); };
        QString phonenumber() const { return m_phonenumber?m_phonenumber->text():QString(); };
        QString email() const { return m_email?m_email->text():QString(); };
        QString company() const { return m_company?m_company->text():QString(); };
        QString faxnumber() const { return m_faxnumber?m_faxnumber->text():QString(); };
        QString mobilenumber() const { return m_mobilenumber?m_mobilenumber->text():QString(); };

    private:
        QLineEdit *m_firstname;
        QLineEdit *m_lastname;
        QLineEdit *m_phonenumber;
        QLineEdit *m_email;
        QLineEdit *m_company;
        QLineEdit *m_faxnumber;
        QLineEdit *m_mobilenumber;
};
#endif

