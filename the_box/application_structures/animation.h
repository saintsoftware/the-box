/* turned on during attack animation */

int combat_attack_animation;
int walk_animation;



typedef struct _LIMdlFrame LIMdlFrame;
struct _LIMdlFrame
{
	LIMatVector scale;
	LIMatTransform transform;
};

typedef struct _LIMdlAnimation LIMdlAnimation;
struct _LIMdlAnimation
{
	int length;
	char* name;
	float blendin; /* TODO: Not used anymore, remove. */
	float blendout; /* TODO: Not used anymore, remove. */
	struct
	{
		int count;
		LIMdlFrame* array;
	} buffer;
	struct
	{
		int count;
		char** array;
	} channels;
};

LIAPICALL (LIMdlAnimation*, animation_new, ());

LIAPICALL (LIMdlAnimation*, animation_new_copy, (
	const LIMdlAnimation* anim));

LIAPICALL (LIMdlAnimation*, limdl_animation_new_from_data, (
	LIArcReader* reader));

LIAPICALL (LIMdlAnimation*, limdl_animation_new_from_file, (
	const char* path));

LIAPICALL (int, limdl_animation_init_copy, (
	LIMdlAnimation*       self,
	const LIMdlAnimation* anim));

LIAPICALL (void, limdl_animation_free, (
	LIMdlAnimation* self));

LIAPICALL (int, limdl_animation_insert_channel, (LIMdlAnimation* self, const char* name));

LIAPICALL (void, limdl_animation_clear, (
	LIMdlAnimation* self));

LIAPICALL (int, limdl_animation_read, (
	LIMdlAnimation* self,
	LIArcReader*    reader,
	int             version));

LIAPICALL (int, limdl_animation_get_channel, (
	LIMdlAnimation* self,
	const char*     name));

LIAPICALL (float, limdl_animation_get_duration, (
	const LIMdlAnimation* self));

LIAPICALL (int, limdl_animation_get_length, (
	const LIMdlAnimation* self));

LIAPICALL (int, limdl_animation_set_length, (
	LIMdlAnimation* self,
	int             value));

LIAPICALL (int, limdl_animation_set_transform, (
	LIMdlAnimation*       self,
	const char*           name,
	int                   frame,
	float                 scale,
	const LIMatTransform* value));

LIAPICALL (int, limdl_animation_get_transform, (
	LIMdlAnimation* self,
	const char*     name,
	float           secs,
	float*          scale,
	LIMatTransform* value));

#endif

#include "lipsofsuna/system.h"
#include "model-animation.h"

#define LIMDL_ANIMATION_VERSION 0x00000001
#define LIMDL_ANIMATION_VERSION_2 0x00000002
#define LIMDL_ANIMATION_TIMESCALE 0.02f

static void private_frame_transform (
	LIMdlAnimation* self,
	int             chan,
	int             frame,
	float*          scale,
	LIMatTransform* value);

static int private_read (
	LIMdlAnimation* self,
	LIArcReader*    reader);


 
LIMdlAnimation* limdl_animation_new ()
{
	LIMdlAnimation* self;

	self = lisys_calloc (1, sizeof (LIMdlAnimation));
	if (self == NULL)
		return NULL;

	return self;
}


LIMdlAnimation* limdl_animation_new_copy (
	const LIMdlAnimation* anim)
{
	LIMdlAnimation* self;

	self = lisys_calloc (1, sizeof (LIMdlAnimation));
	if (self == NULL)
		return NULL;
	if (!limdl_animation_init_copy (self, anim))
	{
		limdl_animation_free (self);
		return NULL;
	}

	return self;
}

/**
 * \brief Creates an animation from a stream reader.
 * \param reader Stream reader.
 * \return New animation, or NULL.
 */
 
LIMdlAnimation* limdl_animation_new_from_data (
	LIArcReader* reader)
{
	LIMdlAnimation* self;

	/* Allocate self. */
	self = lisys_calloc (1, sizeof (LIMdlAnimation));
	if (self == NULL)
		return NULL;

	/* Read from the stream. */
	if (!private_read (self, reader))
	{
		limdl_animation_free (self);
		return NULL;
	}

	return self;
}

/**
 * \brief Creates an animation from a file.
 * \param path File path.
 * \return New animation, or NULL.
 */
LIMdlAnimation* limdl_animation_new_from_file (
	const char* path)
{
	LIArcReader* reader;
	LIMdlAnimation* self;

	reader = liarc_reader_new_from_file (path);
	if (reader == NULL)
		return NULL;
	self = limdl_animation_new_from_data (reader);
	liarc_reader_free (reader);

	return self;
}

/**
 * \brief Copies the animation.
 * \param self Animation.
 * \param anim Animation.
 * \return Nonzero on success.
 */
int limdl_animation_init_copy (
	LIMdlAnimation*       self,
	const LIMdlAnimation* anim)
{
	int i;

	/* Allocate self. */
	self->length = anim->length;
	self->blendin = anim->blendin;
	self->blendout = anim->blendout;
	if (anim->name != NULL)
		self->name = lisys_string_dup (anim->name);

	/* Copy channels. */
	if (anim->channels.count)
	{
		self->channels.array = lisys_calloc (anim->channels.count, sizeof (char*));
		if (self->channels.array == NULL)
			return 0;
		self->channels.count = anim->channels.count;
		for (i = 0 ; i < self->channels.count ; i++)
		{
			self->channels.array[i] = lisys_string_dup (anim->channels.array[i]);
			if (self->channels.array[i] == NULL)
				return 0;
		}
	}

	/* Copy frames. */
	if (anim->buffer.count)
	{
		self->buffer.array = lisys_calloc (anim->buffer.count, sizeof (LIMdlFrame));
		if (self->buffer.array == NULL)
			return 0;
		self->buffer.count = anim->buffer.count;
		memcpy (self->buffer.array, anim->buffer.array,
			self->buffer.count * sizeof (LIMdlFrame));
	}

	return 1;
}

/**
 * \brief Frees the animation.
 * \param self Animation.
 */
void limdl_animation_free (
	LIMdlAnimation* self)
{
	limdl_animation_clear (self);
	lisys_free (self);
}

/**
 * \brief Adds a channel to the animation.
 *
 * If the channel exists already, nothing is done.
 *
 * \param self Animation.
 * \param name Node name.
 * \return Nonzero on success.
 */
int limdl_animation_insert_channel (
	LIMdlAnimation* self,
	const char*     name)
{
	int chan;
	int frame;
	char* str;
	char** tmp;
	LIMdlFrame* dstframe;
	LIMdlFrame* srcframe;
	LIMdlFrame* buffer = NULL;

	/* Check for existence. */
	if (limdl_animation_get_channel (self, name) != -1)
		return 1;

	/* Duplicate the name. */
	str = lisys_string_dup (name);
	if (str == NULL)
		return 0;

	/* Rebuild the transformation buffer. */
	if (self->length)
	{
		buffer = lisys_calloc ((self->channels.count + 1) * self->length, sizeof (LIMdlFrame));
		if (buffer == NULL)
		{
			lisys_free (str);
			return 0;
		}
		for (frame = 0 ; frame < self->length ; frame++)
		{
			for (chan = 0 ; chan < self->channels.count ; chan++)
			{
				srcframe = self->buffer.array + self->channels.count * frame + chan;
				dstframe = buffer + (self->channels.count + 1) * frame + chan;
				dstframe->scale = srcframe->scale;
				dstframe->transform = srcframe->transform;
			}
			dstframe = buffer + (self->channels.count + 1) * frame + chan;
			dstframe->scale = limat_vector_init (1.0f, 1.0f, 1.0f);
			dstframe->transform = limat_transform_identity ();
		}
	}

	/* Allocate a new channel. */
	tmp = lisys_realloc (self->channels.array, (self->channels.count + 1) * sizeof (char*));
	if (tmp == NULL)
	{
		lisys_free (buffer);
		lisys_free (str);
		return 0;
	}
	self->channels.array = tmp;
	self->channels.array[self->channels.count] = str;
	self->channels.count++;

	/* Use the new transformation buffer. */
	if (self->length)
	{
		lisys_free (self->buffer.array);
		self->buffer.array = buffer;
		self->buffer.count = self->channels.count * self->length;
	}

	return 1;
}

/**
 * \brief Clears the name and channels of the animation.
 * \param self Animation.
 */
void limdl_animation_clear (
	LIMdlAnimation* self)
{
	int i;

	if (self->channels.array != NULL)
	{
		for (i = 0 ; i < self->channels.count ; i++)
			lisys_free (self->channels.array[i]);
		lisys_free (self->channels.array);
	}
	lisys_free (self->buffer.array);
	lisys_free (self->name);
}

/**
 * \brief Reads the animation from a stream.
 * \param self Animation.
 * \param reader Stream reader.
 * \param version Format version.
 * \return Nonzero on success.
 */
int limdl_animation_read (
	LIMdlAnimation* self,
	LIArcReader*    reader,
	int             version)
{
	int i;
	uint32_t count0;
	uint32_t count1;
	LIMatTransform* transform;

	/* Read the header. */
	if (!liarc_reader_get_text (reader, "", &self->name) ||
	    !liarc_reader_get_uint32 (reader, &count0) ||
	    !liarc_reader_get_uint32 (reader, &count1))
		return 0;

	/* Allocate channels. */
	self->channels.count = count0;
	if (count0)
	{
		self->channels.array = lisys_calloc (count0, sizeof (char*));
		if (self->channels.array == NULL)
			return 0;
	}

	/* Read channels. */
	for (i = 0 ; i < self->channels.count ; i++)
	{
		if (!liarc_reader_get_text (reader, "", self->channels.array + i))
			return 0;
	}

	/* Allocate frames. */
	self->length = count1;
	self->buffer.count = count0 * count1;
	if (self->buffer.count)
	{
		self->buffer.array = lisys_calloc (self->buffer.count, sizeof (LIMdlFrame));
		if (self->buffer.array == NULL)
			return 0;
	}

	/* Read frames. */
	for (i = 0 ; i < self->buffer.count ; i++)
	{
		transform = &self->buffer.array[i].transform;
		if (!liarc_reader_get_float (reader, &transform->position.x) ||
			!liarc_reader_get_float (reader, &transform->position.y) ||
			!liarc_reader_get_float (reader, &transform->position.z) ||
			!liarc_reader_get_float (reader, &transform->rotation.x) ||
			!liarc_reader_get_float (reader, &transform->rotation.y) ||
			!liarc_reader_get_float (reader, &transform->rotation.z) ||
			!liarc_reader_get_float (reader, &transform->rotation.w))
			return 0;
		if (version == LIMDL_ANIMATION_VERSION_2)
		{
			if (!liarc_reader_get_float (reader, &self->buffer.array[i].scale.x) ||
				!liarc_reader_get_float (reader, &self->buffer.array[i].scale.y) ||
				!liarc_reader_get_float (reader, &self->buffer.array[i].scale.z))
				return 0;
		}
		else
		{
			self->buffer.array[i].scale = limat_vector_init (1.0f, 1.0f, 1.0f);
		}
	}

	return 1;
}

/**
 * \brief Gets the index of a channel.
 *
 * \param self Animation.
 * \param name Channel name.
 * \return Channel index or -1.
 */
int limdl_animation_get_channel (
	LIMdlAnimation* self,
	const char*     name)
{
	int i;

	for (i = 0 ; i < self->channels.count ; i++)
	{
		if (!strcmp (self->channels.array[i], name))
			return i;
	}

	return -1;
}

/**
 * \brief Gets the duration of the animation in seconds.
 *
 * The return value is guaranteed to be greater than zero. If the animation
 * has one or less frames, the return value is one second.
 *
 * \param self Animation.
 * \return Duration in seconds.
 */
float limdl_animation_get_duration (
	const LIMdlAnimation* self)
{
	if (self->length > 1)
		return (self->length - 1) * LIMDL_ANIMATION_TIMESCALE;
	return 1.0f;
}

/**
 * \brief Gets the number of frames in the animation.
 * \param self Animation.
 * \return Number of frames.
 */
int limdl_animation_get_length (
	const LIMdlAnimation* self)
{
	if (!self->channels.count)
		return 0;
	return self->buffer.count / self->channels.count;
}

/**
 * \brief Sets the number of frames in the animation.
 * \param self Animation.
 * \param value Frame count.
 * \return Nonzero on success.
 */
int limdl_animation_set_length (
	LIMdlAnimation* self,
	int             value)
{
	int i;
	LIMdlFrame* tmp;

	if (value == self->length)
		return 1;
	if (!self->channels.count)
	{
		self->length = value;
		return 1;
	}
	if (!value)
	{
		/* Set to empty. */
		lisys_free (self->buffer.array);
		self->buffer.array = NULL;
	}
	else if (value < self->length)
	{
		/* Shrink. */
		tmp = lisys_realloc (self->buffer.array, self->channels.count * value * sizeof (LIMdlFrame));
		if (tmp != NULL)
			self->buffer.array = tmp;
	}
	else
	{
		/* Expand. */
		tmp = lisys_realloc (self->buffer.array, self->channels.count * value * sizeof (LIMdlFrame));
		if (tmp == NULL)
			return 0;
		self->buffer.array = tmp;
		for (i = self->channels.count * self->length ; i < self->channels.count * value ; i++)
		{
			self->buffer.array[i].scale = limat_vector_init (1.0f, 1.0f, 1.0f);
			self->buffer.array[i].transform = limat_transform_identity ();
		}
	}
	self->length = value;
	self->buffer.count = self->channels.count * self->length;

	return 1;
}

/**
 * \brief Sets the node transformation.
 * \param self Animation.
 * \param name Channel name.
 * \param frame Frame number.
 * \param scale Scale factor.
 * \param value Node transformation.
 * \return Nonzero on success.
 */
int limdl_animation_set_transform (
	LIMdlAnimation*       self,
	const char*           name,
	int                   frame,
	float                 scale,
	const LIMatTransform* value)
{
	int chan;

	lisys_assert (frame >= 0);
	lisys_assert (frame < self->length);

	chan = limdl_animation_get_channel (self, name);
	if (chan == -1)
		return 0;
	self->buffer.array[self->channels.count * frame + chan].scale.x = scale;
	self->buffer.array[self->channels.count * frame + chan].scale.y = scale;
	self->buffer.array[self->channels.count * frame + chan].scale.z = scale;
	self->buffer.array[self->channels.count * frame + chan].transform = *value;

	return 1;
}

/**
 * \brief Gets the node transformation.
 * \param self Animation.
 * \param name Channel name.
 * \param secs Animation position.
 * \param scale Return location for the scale factor.
 * \param value Return location for the transformation.
 * \return Nonzero on success.
 */
int limdl_animation_get_transform (
	LIMdlAnimation* self,
	const char*     name,
	float           secs,
	float*          scale,
	LIMatTransform* value)
{
	int chan;
	int frame;
	int len;
	float s0;
	float s1;
	float blend;
	float frames;
	LIMatTransform t0;
	LIMatTransform t1;

	chan = limdl_animation_get_channel (self, name);
	if (chan == -1)
		return 0;
	len = limdl_animation_get_length (self);
	if (len == 0)
		return 0;

	frames = secs / LIMDL_ANIMATION_TIMESCALE;
	frame = (int) frames;
	if (frame < 0)
		private_frame_transform (self, chan, 0, scale, value);
	else if (frame >= len - 1)
		private_frame_transform (self, chan, len - 1, scale, value);
	else
	{
		blend = frames - frame;
		private_frame_transform (self, chan, frame, &s0, &t0);
		private_frame_transform (self, chan, frame + 1, &s1, &t1);
		*scale = (1.0f - blend) * s0 + blend * s1;
		value->position = limat_vector_lerp (t1.position, t0.position, blend);
		value->rotation = limat_quaternion_nlerp (t1.rotation, t0.rotation, blend);
	}

	return 1;
}

/*****************************************************************************/

static void private_frame_transform (
	LIMdlAnimation* self,
	int             chan,
	int             frame,
	float*          scale,
	LIMatTransform* value)
{
	*scale = self->buffer.array[self->channels.count * frame + chan].scale.x;
	*value = self->buffer.array[self->channels.count * frame + chan].transform;
}

static int private_read (
	LIMdlAnimation* self,
	LIArcReader*    reader)
{
	int ret;
	char* id;
	uint32_t size;
	uint32_t version;

	/* Read the magic. */
	if (!liarc_reader_check_text (reader, "lips/ani", ""))
	{
		lisys_error_set (EINVAL, "wrong animation file format");
		return 0;
	}

	/* Read header chunk size. */
	if (!liarc_reader_get_uint32 (reader, &size))
		return 0;
	if (size != 4)
	{
		lisys_error_set (LISYS_ERROR_VERSION, "invalid animation header block");
		return 0;
	}

	/* Read the version. */
	if (!liarc_reader_get_uint32 (reader, &version))
		return 0;
	if (version != LIMDL_ANIMATION_VERSION &&
	    version != LIMDL_ANIMATION_VERSION_2)
	{
		lisys_error_set (LISYS_ERROR_VERSION, "animation version mismatch");
		return 0;
	}

	/* Read chunks. */
	while (!liarc_reader_check_end (reader))
	{
		id = NULL;
		if (!liarc_reader_get_text (reader, "", &id) ||
		    !liarc_reader_get_uint32 (reader, &size))
		{
			lisys_error_set (LISYS_ERROR_VERSION, "reading chunk failed");
			lisys_free (id);
			return 0;
		}
		if (size > reader->length - reader->pos)
		{
			lisys_error_set (LISYS_ERROR_VERSION, "invalid chunk size for `%s'", id);
			lisys_free (id);
			return 0;
		}
		if (!strcmp (id, "ani"))
		{
			ret = limdl_animation_read (self, reader, version);
		}
		else
		{
			if (!liarc_reader_skip_bytes (reader, size))
			{
				lisys_error_set (LISYS_ERROR_VERSION, "failed to skip block `%s'", id);
				lisys_free (id);
				return 0;
			}
			ret = 1;
		}
		if (!ret)
		{
			lisys_error_set (LISYS_ERROR_VERSION, "failed to read block `%s'", id);
			lisys_free (id);
			return 0;
		}
		lisys_free (id);
	}

	return 1;
}

/** @} */
/** @} */
