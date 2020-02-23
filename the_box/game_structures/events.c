/* Lips of Suna
 * Copyright© 2007-2012 Lips of Suna development team.
 *
 * Lips of Suna is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Lips of Suna is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Lips of Suna. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \addtogroup LIMai Main
 * @{
 * \addtogroup LIMaiEvent Event
 * @{
 */

#include "main-event.h"

/**
 * \brief Creates a new event.
 * \param type Event type.
 * \param args Variable argument list.
 * \return New event, or NULL.
 */
LIMaiEvent* limai_event_new (
	const char* type,
	va_list     args)
{
	const char* name;
	const void* pptr;
	const char* pstr;
	LIMaiEvent* self;
	LIMaiEventField* field;

	/* Allocate self. */
	self = lisys_calloc (1, sizeof (LIMaiEvent));
	if (self == NULL)
		return 0;

	/* Save the type. */
	self->type = lisys_string_dup (type);
	if (self->type == NULL)
	{
		lisys_free (self);
		return 0;
	}

	/* Copy the fields. */
	while (1)
	{
		/* Get the next field. */
		lisys_assert (self->fields.count < LIMAI_EVENT_FIELDS_MAX);
		field = self->fields.array + self->fields.count;

		/* Get the field name. */
		name = va_arg (args, char*);
		if (name == NULL)
			break;
		field->name = lisys_string_dup (name);
		if (field->name == NULL)
		{
			limai_event_free (self);
			return NULL;
		}

		/* Get the field value. */
		field->type = va_arg (args, int);
		if (field->type == LIMAI_FIELD_BOOL)
		{
			field->value_bool = va_arg (args, int);
		}
		else if (field->type == LIMAI_FIELD_FLOAT)
		{
			field->value_float = va_arg (args, double);
		}
		else if (field->type == LIMAI_FIELD_INT)
		{
			field->value_int = va_arg (args, int);
		}
		else if (field->type == LIMAI_FIELD_STRING)
		{
			pstr = va_arg (args, char*);
			field->value_string = lisys_string_dup (pstr);
			if (field->value_string == NULL)
			{
				limai_event_free (self);
				return NULL;
			}
		}
		else if (field->type == LIMAI_FIELD_PACKET)
		{
			pptr = va_arg (args, void*);
			field->value_packet = liarc_packet_new_readable_copy (pptr);
			if (field->value_packet == NULL)
			{
				limai_event_free (self);
				return NULL;
			}
		}
		else if (field->type == LIMAI_FIELD_VECTOR)
		{
			pptr = va_arg (args, void*);
			field->value_vector = *((LIMatVector*) pptr);
		}
		else
		{
			lisys_assert (0);
			lisys_free (field->name);
			self->fields.count--;
		}

		/* Move to the next field. */
		self->fields.count++;
	}

	return self;
}

/**
 * \brief Frees the event.
 * \param self Event.
 */
void limai_event_free (
	LIMaiEvent* self)
{
	int i;
	LIMaiEventField* field;

	for (i = 0 ; i < self->fields.count ; i++)
	{
		field = self->fields.array + i;
		lisys_free (field->name);
		switch (field->type)
		{
			case LIMAI_FIELD_BOOL:
			case LIMAI_FIELD_FLOAT:
			case LIMAI_FIELD_INT:
			case LIMAI_FIELD_VECTOR:
				break;
			case LIMAI_FIELD_PACKET:
				liarc_packet_free (field->value_packet);
				break;
			case LIMAI_FIELD_STRING:
				lisys_free (field->value_string);
				break;
			default:
				lisys_assert (0);
				break;
		}
	}
	lisys_free (self->type);
	lisys_free (self);
}

/**
 * \brief Creates a Lua table out of the event.
 * \param self Event.
 * \param script Script.
 */
void limai_event_write_script (
	LIMaiEvent*  self,
	LIScrScript* script)
{
	int i;
	LIScrData* data;
	LIMaiEventField* field;
	lua_State* lua;

	/* Create the event table. */
	lua = liscr_script_get_lua (script);
	lua_newtable (lua);

	/* Set the type. */
	lua_pushstring (lua, self->type);
	lua_setfield (lua, -2, "type");

	/* Set the fields. */
	for (i = 0 ; i < self->fields.count ; i++)
	{
		field = self->fields.array + i;
		if (field->type == LIMAI_FIELD_BOOL)
		{
			lua_pushboolean (lua, field->value_bool);
		}
		else if (field->type == LIMAI_FIELD_FLOAT)
		{
			lua_pushnumber (lua, field->value_float);
		}
		else if (field->type == LIMAI_FIELD_INT)
		{
			lua_pushnumber (lua, field->value_int);
		}
		else if (field->type == LIMAI_FIELD_STRING)
		{
			lua_pushstring (lua, field->value_string);
		}
		else if (field->type == LIMAI_FIELD_PACKET)
		{
			data = liscr_data_new (script, lua, field->value_packet, LISCR_SCRIPT_PACKET, liarc_packet_free);
			if (data == NULL)
				break;
			field->type = LIMAI_FIELD_INT;
			field->value_int = 0;
		}
		else if (field->type == LIMAI_FIELD_VECTOR)
		{
			data = liscr_data_new_alloc (script, lua, sizeof (LIMatVector), LISCR_SCRIPT_VECTOR);
			if (data == NULL)
				break;
			*((LIMatVector*) liscr_data_get_data (data)) = field->value_vector;
		}
		else
		{
			lisys_assert (0);
			lua_pushnil (lua);
		}

		/* Set field. */
		lua_setfield (lua, -2, field->name);
	}
}

/** @} */
/** @} */
