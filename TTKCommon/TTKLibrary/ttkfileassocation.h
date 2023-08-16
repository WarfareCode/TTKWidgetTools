#ifndef TTKFILEASSOCATION_H
#define TTKFILEASSOCATION_H

/***************************************************************************
 * This file is part of the TTK Library Module project
 * Copyright (C) 2015 - 2023 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QStringList>
#include "ttkmoduleexport.h"

#ifdef Q_OS_WIN
/*! @brief The class of the file assocation.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT TTKFileAssocation
{
    TTK_DECLARE_MODULE(TTKFileAssocation)
public:
    /*!
     * Add file assocation by suffix.
     */
    void append(const QString& suffix);
    /*!
     * Remove file assocation by suffix.
     */
    void remove(const QString& suffix);

    /*!
     * Check current suffix is or not file assocated.
     */
    bool exist(const QString& suffix) const;

    /*!
     * Return current file assocation keys.
     */
    QStringList keys() const;

private:
    /*!
     * Add class level file assocation by suffix.
     */
    void appendClass(const QString& suffix);
    /*!
     * Add software level file assocation by suffix.
     */
    void appendSoftware(const QString& suffix);
    /*!
     * Add exts level file assocation by suffix.
     */
    void appendFileExts(const QString& suffix);

    /*!
     * Remove class level file assocation by suffix.
     */
    void removeClass(const QString& suffix);
    /*!
     * Remove software level file assocation by suffix.
     */
    void removeSoftware(const QString& suffix);
    /*!
     * Remove exts level file assocation by suffix.
     */
    void removeFileExts(const QString& suffix);

};
#endif

#endif // TTKFILEASSOCATION_H
