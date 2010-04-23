/*
 * Copyright © 2009 Emmanuel Pacaud
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author:
 * 	Emmanuel Pacaud <emmanuel@gnome.org>
 */

#include <lsmsvggelement.h>
#include <lsmdebug.h>
#include <stdio.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_g_element_get_node_name (LsmDomNode *node)
{
	return "g";
}

/* GGElement implementation */

/* LsmSvgElement implementation */

/* LsmSvgGElement implementation */

LsmDomNode *
lsm_svg_g_element_new (void)
{
	return g_object_new (LSM_TYPE_SVG_G_ELEMENT, NULL);
}

static void
lsm_svg_g_element_init (LsmSvgGElement *self)
{
}

/* LsmSvgGElement class */


static void
lsm_svg_g_element_class_init (LsmSvgGElementClass *s_g_class)
{
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (s_g_class);

	parent_class = g_type_class_peek_parent (s_g_class);

	d_node_class->get_node_name = lsm_svg_g_element_get_node_name;
}

G_DEFINE_TYPE (LsmSvgGElement, lsm_svg_g_element, LSM_TYPE_SVG_ELEMENT)
