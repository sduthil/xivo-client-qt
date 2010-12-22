/* XiVO Client
 * Copyright (C) 2007-2010, Proformatique
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

#ifndef __RECORDSPANEL_H__
#define __RECORDSPANEL_H__

#include <QtGui>

#include <xletinterface.h>
#include <xlet.h>

class SearchWidget;
class ResultsWidget;

class XletRecords : public XLet
{
    Q_OBJECT
    public:
        XletRecords(QWidget *parent=0);
        ~XletRecords();
        void recordResults(const QVariantMap &);
        static void recordResults_t(const QVariantMap & p, void * udata) {
                ((XletRecords*)udata)->recordResults(p);
        };

    signals:
        void update();
    private slots:
        void onViewClick(const QModelIndex &);
        void onViewDoubleClick(const QModelIndex &);
        void pevent(QMouseEvent *);
    private:
        int m_lastPressed;

        QVBoxLayout * m_xletLayout;
        QLabel * m_titlewidget;
        QFrame * m_qhline1;
        QFrame * m_qhline2;
        SearchWidget * m_searchwidget;
        ResultsWidget * m_resultswidget;

        void clientrequest();
};

class XLetRecordsPlugin : public QObject, XLetInterface
{
    Q_OBJECT
    Q_INTERFACES(XLetInterface)
    public:
        XLet *newXLetInstance(QWidget *parent=0);
};

class SearchWidget : public QWidget
{
    Q_OBJECT
    public:
        SearchWidget(QWidget *parent=0);
        ~SearchWidget();
    private:
        QComboBox * m_researchkind;
        QLineEdit * m_searchwidget;
    private slots:
        void lookup();
};

class ResultsWidget : public QWidget
{
    Q_OBJECT
    public:
        ResultsWidget(QWidget * parent = 0);
        ~ResultsWidget();
    private slots:
        void update();
    private:
        QLabel * m_summary;
};

#endif
