/*
 *  ext3Viewer,ext3Viewer GUI / an ext3 filesystem low level viewer
 *
 *  Copyright (C) 2007 Laurent Sebag & Nathan Periana
 *
 *  This file is part of ext3Viewer.
 *
 *  Ext3Viewer is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Ext3Viewer is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */



#ifndef MACROS_H
#define MACROS_H

#ifdef DEBUG
#define DEBUG_PRINT(string,args) \
        printf("ext3Viewer - DEBUG :\t " string "\n",args);
#else
#define DEBUG_PRINT(string,args)
#endif

#ifdef DEBUG_VERBOSE
#define DEBUG_PRINT_V(string,args) \
        printf("ext3Viewer - DEBUG_V :\t " string "\n",args);
#else
#define DEBUG_PRINT_V(string,args)
#endif

#endif

