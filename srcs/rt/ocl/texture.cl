static float			getTextureValue
(
						__constant t_object		*obj
)
{
	float				texValue;

	texValue = 0.f;
	if (obj->pattern == PSOLID)
		texValue = 1.f;
	return (texValue);
}

static t_texture		textureProperties
(
						__constant t_scene		*scene,
						__constant t_object		*obj,
						float3					normal
)
{
	t_texture			texture;

	texture.texValue = getTextureValue(obj);
	texture.rgb = obj->color * texture.texValue;
	texture.bump_normal = normal;
	return (texture);
}
