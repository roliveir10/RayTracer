# define MAX_OBJECT 64
# define SCENE_ELEMENT 6
# define CAMERA_ELEMENT 3
# define OBJECT_ELEMENT 15

__constant float EPSILON = 0.0001f;
__constant float PI = 0x1.921fb54442d18p1f;
__constant float TAU = 0x1.921fb54442d18p2f;

typedef enum		e_objType
{
	SNONE = -1,
	SPHERE,
	PLAN,
	CYLINDRE,
	CONE,
	CUBE,
	DISK,
	HYPERBOLOID,
	INFHYPERBOLOID,
	INFCYLINDRE,
	INFCONE,
	RECTANGLE,
	TRIANGLE,
	PARABOLOID,
	SADDLE,
	THORUS,
	CAPSULE,
	ELLIPSOID,
	ROUNDEDCONE,
	SPHERE4,
	GOURSAT,
	ROUNDEDBOX
}					t_objType;

typedef enum		e_intersection
{
	INSIDE = -1,
	OUTSIDE = 1,
	NONE = 0
}					t_intersection;

typedef enum			e_pattern
{
	PSOLID = 0
}						t_pattern;

typedef enum			s_material
{
	MNONE = -1,
	MLIGHT,
	MDIFFUSE,
	MTRANSPARENT,
	MSPECULAR
}						t_material;

typedef enum			e_bump
{
	BFLAT,
	BBUMP
}						t_bump;

typedef struct			s_bbox
{
	float3				vmin;
	float3				vmax;
}						t_bbox;

typedef struct			s_object
{
	char				name[16];
	t_objType			type;
	t_material			material;
	float3				origin;
	float3				color;
	int					intensity;
	float3				rotation;
	char				isRotated;
	float3				scale;
	t_bbox				bboxOs;
	t_bbox				bboxWs;
	float				shininess;
	float3				refrac;
	float				opacity;
	float16				w_to_o;
	float16				o_to_w;
	float16				n_to_w;
	t_pattern			pattern;
	t_bump				bump_type;
	char				parsElement[OBJECT_ELEMENT];
}						t_object;

typedef struct			s_rayHit
{
	float				distance;
	float3				normal;
	float3				point;
	float3				viewDir;
	float3				color;
	t_object			obj;
}						t_rayHit;

typedef struct			s_camera
{
	float3				origin;
	float3				rotation;
	float3				direction[3];
	float3				vpUpLeft;
	float				fov;
	float				planeDist;
	float				viewPlaneWidth;
	float				viewPlaneHeight;
	float				xIndent;
	float				yIndent;
	char				parsElement[CAMERA_ELEMENT];
}						t_camera;

typedef struct			s_scene
{
	float3				background;
	t_camera			camera;
	t_object			object[MAX_OBJECT];
	int					nbrObject;
	float				maxDistToPrint;
	t_bbox				bboxWs;
	int					bounceMax;
	int3				work_steps;
	int3				work_dims;
	char				parsElement[SCENE_ELEMENT];
}						t_scene;

typedef struct			s_ray
{
	float3				o;
	float3				dir;
	float				t;
	int					objId;
	float3				hitPos;
	float3				lum_mask;
	float3				lum_acc;
	float				refrac;
	t_intersection		interType;
	bool				complete;
}						t_ray;


typedef struct			s_texture
{
	t_pattern			pattern;
	float				texValue;
	float3				bump_normal;
	float3				rgb;
}						t_texture;
