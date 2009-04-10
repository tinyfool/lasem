/* lsmmathmlscriptelement.h
 *
 * Copyright © 2007-2008  Emmanuel Pacaud
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * Author:
 * 	Emmanuel Pacaud <emmanuel@gnome.org>
 */

#ifndef LSM_MATHML_SCRIPT_ELEMENT_H
#define LSM_MATHML_SCRIPT_ELEMENT_H

#include <lsmmathml.h>
#include <lsmmathmlelement.h>

G_BEGIN_DECLS

typedef enum {
	LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB,
	LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUP,
	LSM_MATHML_SCRIPT_ELEMENT_TYPE_SUB_SUP
} LsmMathmlScriptElementType;

#define LSM_MATHML_TYPE_SCRIPT_ELEMENT             (lsm_mathml_script_element_get_type ())
#define LSM_MATHML_SCRIPT_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_MATHML_TYPE_SCRIPT_ELEMENT, LsmMathmlScriptElement))
#define LSM_MATHML_SCRIPT_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_MATHML_TYPE_SCRIPT_ELEMENT, LsmMathmlScriptElementClass))
#define LSM_MATHML_IS_SCRIPT_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_MATHML_TYPE_SCRIPT_ELEMENT))
#define LSM_MATHML_IS_SCRIPT_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_MATHML_TYPE_SCRIPT_ELEMENT))
#define LSM_MATHML_SCRIPT_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_MATHML_TYPE_SCRIPT_ELEMENT, LsmMathmlScriptElementClass))

typedef struct _GMathmlScriptElementClass LsmMathmlScriptElementClass;

struct _GMathmlScriptElement {
	LsmMathmlElement	element;

	LsmMathmlElement *base;
	LsmMathmlElement *subscript;
	LsmMathmlElement *superscript;

	double subscript_offset;
	double superscript_offset;

	LsmMathmlScriptElementType type;

	LsmMathmlLengthAttribute subscript_shift;
	LsmMathmlLengthAttribute superscript_shift;

	LsmMathmlDisplay display;
};

struct _GMathmlScriptElementClass {
	LsmMathmlElementClass  parent_class;
};

GType lsm_mathml_script_element_get_type (void);

LsmDomNode * 	lsm_mathml_sub_element_new 	(void);
LsmDomNode * 	lsm_mathml_sup_element_new 	(void);
LsmDomNode * 	lsm_mathml_sub_sup_element_new 	(void);

G_END_DECLS

#endif
