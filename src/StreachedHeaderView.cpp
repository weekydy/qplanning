/*
 * ./StreachedHeaderView.cpp
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
/// \file StreachedHeaderView.cpp
/// \brief HeaderVieuw with steach position capability.
/// \author Lameire Alexis
///

#include "StreachedHeaderView.h"

StreachedHeaderView::StreachedHeaderView(Qt::Orientation orientation, QWidget* parent) :
        QHeaderView(orientation, parent),
        is_streached(true)
{
}

bool StreachedHeaderView::get_streach_stat()
{
        return is_streached;
}

void StreachedHeaderView::set_streach_stat(bool activate)
{
        is_streached = activate;
}

void StreachedHeaderView::set_row_streach(int row, int streach_factor)
{
        streach.insert(row, streach_factor);
}

void StreachedHeaderView::resizeEvent(QResizeEvent* event)
{
        QHeaderView::resizeEvent(event);
        if (is_streached)
        {
                int total = 0;
                for (int i = 0; i < count(); ++i)
                {
                        total += streach.value(i, 1);
                }

                int total_size = 0;
                for (int i = 0; i < count() - 1; ++i)
                {
                        qreal factor = streach.value(i, 1) / static_cast<qreal>(total);

                        int section_size = factor * (orientation() == Qt::Horizontal ? width() : height());
                        section_size = qMax(minimumSectionSize(), section_size);
                        resizeSection(i, section_size);
                        total_size += section_size;
                }
                // avoid rounding errors, give rest to the last section
                resizeSection(count() - 1, width() - total_size);
        }
}
