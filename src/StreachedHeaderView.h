/*
 * ./StreachedHeaderView.h
 * Copyright (C) 2010 Lameire Alexis
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
///
/// \file StreachedHeaderView.h
/// \brief add QTableView with steach position capability.
/// \author Lameire Alexis
///
#ifndef STREACHEDTABLEVIEW_H
#define STREACHEDTABLEVIEW_H

#include <QMap>
#include <QHeaderView>

///
/// \class StreachedHeaderView StreachedHeaderView.h
/// \brief HeaderView with steach position capability.
///
class StreachedHeaderView : public QHeaderView
{
        Q_OBJECT
        public:
                ///
                /// \brief default constructor
                ///
        explicit StreachedHeaderView(Qt::Orientation orientation, QWidget* parent = 0);
                ///
                /// \brief get the streach statut
                ///
                bool get_streach_stat();
                ///
                /// \brief set the streach statut
                /// \arg activate value to set to streach
                ///
                void set_streach_stat(bool activate = true);
                ///
                /// \brief define the streach for a row
                /// \arg row row where the streach must be fix
                /// \arg streach streach associated with this row
                ///
                void set_row_streach(int row, int streach_factor);

        protected:
                ///
                /// \reimp
                ///
                void resizeEvent(QResizeEvent* event);

        private:
                bool is_streached;
                QMap<int, int> streach;

};

#endif // STREACHEDTABLEVIEW_H
