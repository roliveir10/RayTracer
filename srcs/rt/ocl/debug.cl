static void			debugPrintObject(__global t_object* obj)
{
	float16			ow;
	float16			wo;
	float16			nw;

	ow = mat44Transpose(obj->o_to_w);
	wo = mat44Transpose(obj->w_to_o);
	nw = mat44Transpose(obj->n_to_w);

	printf("\n\nObject\n"
			"\tpos %g %g %g | scale %g %g %g | rot %g %g %g \n"
			"\tobj->o_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
			"\tobj->w_to_o: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
			"\tobj->n_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
			,
	obj->origin.x, obj->origin.y, obj->origin.z, obj->scale.x, obj->scale.y, obj->scale.z, obj->rotation.x, obj->rotation.y, obj->rotation.z,
	ow.s0, ow.s1, ow.s2, ow.s3, ow.s4, ow.s5, ow.s6, ow.s7, ow.s8, ow.s9, ow.sA, ow.sB, ow.sC, ow.sD, ow.sE, ow.sF,
	wo.s0, wo.s1, wo.s2, wo.s3, wo.s4, wo.s5, wo.s6, wo.s7, wo.s8, wo.s9, wo.sA, wo.sB, wo.sC, wo.sD, wo.sE, wo.sF,
	nw.s0, nw.s1, nw.s2, nw.s3, nw.s4, nw.s5, nw.s6, nw.s7, nw.s8, nw.s9, nw.sA, nw.sB, nw.sC, nw.sD, nw.sE, nw.sF
	);
}
