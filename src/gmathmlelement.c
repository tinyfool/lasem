/* gmathmlelement.c
 *
 * Copyright (C) 2007  Emmanuel Pacaud
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

#include <gmathmlelement.h>

static GObjectClass *parent_class;

static const GMathmlBbox null_bbox = {0.0,0.0,0.0};

/* GDomNode implementation */

static void
gmathml_element_post_new_child (GDomNode *parent, GDomNode *child)
{
}

static void
gmathml_element_pre_remove_child (GDomNode *parent, GDomNode *child)
{
}

/* GDomElement implementation */

static void
gmathml_element_set_attribute (GDomElement *self, const char* name, const char *value)
{
	GMathmlElementClass *m_element_class = GMATHML_ELEMENT_GET_CLASS(self);

	gmathml_attribute_map_set_attribute (m_element_class->attributes, self,
					     name, value);
}

const char *
gmathml_element_get_attribute (GDomElement *self, const char *name)
{
	GMathmlElementClass *m_element_class = GMATHML_ELEMENT_GET_CLASS(self);

	return gmathml_attribute_map_get_attribute (m_element_class->attributes, self, name);
}

/* GMathmlElement implementation */

static void
_update_attributes (GMathmlElement *self)
{
	GDomNode *parent;

	parent = GDOM_NODE (self)->parent_node;

	if (GMATHML_IS_ELEMENT (parent)) {
		gmathml_attribute_script_level_parse (&self->style_attrs.script_level,
						      GMATHML_ELEMENT (parent)->style_attrs.script_level.value);
		gmathml_attribute_boolean_parse (&self->style_attrs.display_style,
						 GMATHML_ELEMENT (parent)->style_attrs.display_style.value);
	} else {
		gmathml_attribute_script_level_parse (&self->style_attrs.script_level, 0.0);
		gmathml_attribute_boolean_parse (&self->style_attrs.display_style, FALSE);
	}

	gmathml_attribute_double_parse (&self->style_attrs.script_size_multiplier, 0.71);
	gmathml_attribute_color_parse (&self->style_attrs.background, 0.0, 0.0, 0.0, 0.0);

/*        gmathml_boolean_attribute_set_default (&m_element->style_attrs.display_style, FALSE);*/
/*        gmathml_double_attribute_set_default (&m_element->style_attrs.script_size_multiplier, 0.71);*/
/*        gmathml_length_attribute_set_default (&m_element->style_attrs.script_min_size, 1.0, GMATHML_UNIT_PX);*/
	/* FIXME background */
/*        gmathml_length_attribute_set_default (&m_element->style_attrs.very_very_thin_math_space,*/
/*                                              0.0555556, GMATHML_UNIT_EM);*/
/*        gmathml_length_attribute_set_default (&m_element->style_attrs.very_thin_math_space,*/
/*                                              0.111111, GMATHML_UNIT_EM);*/
/*        gmathml_length_attribute_set_default (&m_element->style_attrs.thin_math_space,*/
/*                                              0.166667, GMATHML_UNIT_EM);*/
/*        gmathml_length_attribute_set_default (&m_element->style_attrs.medium_math_space,*/
/*                                              0.222222, GMATHML_UNIT_EM);*/
/*        gmathml_length_attribute_set_default (&m_element->style_attrs.thick_math_space,*/
/*                                              0.277778, GMATHML_UNIT_EM);*/
/*        gmathml_length_attribute_set_default (&m_element->style_attrs.very_thick_math_space,*/
/*                                              0.333333, GMATHML_UNIT_EM);*/
/*        gmathml_length_attribute_set_default (&m_element->style_attrs.very_very_thick_math_space,*/
/*                                              0.388889, GMATHML_UNIT_EM);*/
}

void
gmathml_element_update_attributes (GMathmlElement *element)
{
	GMathmlElementClass *element_class;
	GDomNode *node;

	g_return_if_fail (GMATHML_IS_ELEMENT (element));

	g_message ("Update %s", gdom_node_get_node_name (GDOM_NODE (element)));

	element_class = GMATHML_ELEMENT_GET_CLASS (element);

	if (element_class->update_attributes)
		element_class->update_attributes (element);

	for (node = GDOM_NODE (element)->first_child; node != NULL; node = node->next_sibling)
		if (GMATHML_IS_ELEMENT (node))
			gmathml_element_update_attributes (GMATHML_ELEMENT (node));
}

const GMathmlBbox *
gmathml_element_measure (GMathmlElement *element, GMathmlView *view)
{
	GMathmlElementClass *element_class;

	g_return_val_if_fail (GMATHML_IS_ELEMENT (element), &null_bbox);

	element_class = GMATHML_ELEMENT_GET_CLASS (element);

	g_return_val_if_fail (element_class != NULL, &null_bbox);

	if (!element->measure_done) {
		if (element_class->measure) {
			element->bbox = *(element_class->measure (element, view));

			g_message ("BBox (%s) %g, %g, %g",
				   gdom_node_get_node_name (GDOM_NODE (element)),
				   element->bbox.width, element->bbox.height, element->bbox.depth);
		} else {
			element->bbox.width = 0.0;
			element->bbox.height = 0.0;
			element->bbox.depth = 0.0;
		}

		element->measure_done = TRUE;
	}

	return &element->bbox;
}

void
gmathml_element_layout (GMathmlElement *self, GMathmlView *view,
			double x, double y, const GMathmlBbox *bbox)
{
	GMathmlElementClass *element_class;

	g_return_if_fail (GMATHML_IS_ELEMENT (self));

	element_class = GMATHML_ELEMENT_GET_CLASS (self);

	g_return_if_fail (element_class != NULL);

	g_message ("Assigned bbox for %s = %g, %g, %g",
		   gdom_node_get_node_name (GDOM_NODE (self)), bbox->width, bbox->height, bbox->depth);

	self->x = x;
	self->y = y;

	if (element_class->layout)
		element_class->layout (self, view, x, y, bbox);
}

static void
_render (GMathmlElement *element, GMathmlView *view)
{
	GDomNode *node;

	for (node = GDOM_NODE (element)->first_child; node != NULL; node = node->next_sibling)
		if (GMATHML_IS_ELEMENT (node))
		    gmathml_element_render (GMATHML_ELEMENT (node), view);
}

void
gmathml_element_render (GMathmlElement *element, GMathmlView *view)
{
	GMathmlElementClass *element_class = GMATHML_ELEMENT_GET_CLASS (element);

	g_return_if_fail (element_class != NULL);

	if (element_class->render)
		element_class->render (element, view);
}

static void
gmathml_element_init (GMathmlElement *element)
{
}

static void
gmathml_element_finalize (GObject *object)
{
	GMathmlElementClass *m_element_class = GMATHML_ELEMENT_GET_CLASS (object);

	gmathml_attribute_map_free_attributes (m_element_class->attributes, object);

	parent_class->finalize (object);
}

/* GMathmlElement class */

void
gmathml_element_class_add_element_attributes (GMathmlElementClass *m_element_class)
{
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "class",
					     offsetof (GMathmlElement, element_attrs.class_name));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "id",
					     offsetof (GMathmlElement, element_attrs.id));
}

void
gmathml_element_class_add_style_attributes (GMathmlElementClass *m_element_class)
{
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "scriptlevel",
					     offsetof (GMathmlElement, style_attrs.script_level));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "display",
					     offsetof (GMathmlElement, style_attrs.display_style));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "scriptsizemultiplier",
					     offsetof (GMathmlElement, style_attrs.script_size_multiplier));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "scriptminsize",
					     offsetof (GMathmlElement, style_attrs.script_min_size));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "background",
					     offsetof (GMathmlElement, style_attrs.background));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "veryverythinmathspace",
					     offsetof (GMathmlElement, style_attrs.very_very_thin_math_space));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "verythinmathspace",
					     offsetof (GMathmlElement, style_attrs.very_thin_math_space));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "thinmathspace",
					     offsetof (GMathmlElement, style_attrs.thin_math_space));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "mediummathspace",
					     offsetof (GMathmlElement, style_attrs.medium_math_space));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "thickmathspace",
					     offsetof (GMathmlElement, style_attrs.thick_math_space));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "verythickmathspace",
					     offsetof (GMathmlElement, style_attrs.very_thick_math_space));
	gmathml_attribute_map_add_attribute (m_element_class->attributes, "veryverythickmathspace",
					     offsetof (GMathmlElement, style_attrs.very_very_thick_math_space));
}

static void
gmathml_element_class_init (GMathmlElementClass *m_element_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (m_element_class);
	GDomNodeClass *d_node_class = GDOM_NODE_CLASS (m_element_class);
	GDomElementClass *d_element_class = GDOM_ELEMENT_CLASS (m_element_class);

	parent_class = g_type_class_peek_parent (m_element_class);

	object_class->finalize = gmathml_element_finalize;

	d_node_class->post_new_child = gmathml_element_post_new_child;
	d_node_class->pre_remove_child = gmathml_element_pre_remove_child;

	d_element_class->get_attribute = gmathml_element_get_attribute;
	d_element_class->set_attribute = gmathml_element_set_attribute;

	m_element_class->update_attributes = _update_attributes;
	m_element_class->render = _render;

	m_element_class->attributes = gmathml_attribute_map_new ();

	gmathml_element_class_add_element_attributes (m_element_class);
	gmathml_element_class_add_style_attributes (m_element_class);
}

G_DEFINE_ABSTRACT_TYPE (GMathmlElement, gmathml_element, GDOM_TYPE_ELEMENT)
