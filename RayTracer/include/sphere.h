#ifndef SPHERE_H
#define SPHERE_H

class sphere : public hittable {

	public:

		sphere(const point3& center, double radius, shared_ptr<material> mat)
			: center(center), radius(std::fmax(0, radius)), mat(mat) {}

		bool hit(const ray& r, interval ray_t, hit_record& rec) const override {

			auto a = dot(r.direction(), r.direction());
			auto h = dot(r.direction(), this->center - r.at(0));
			auto c = dot(this->center - r.at(0), this->center - r.at(0)) - (this->radius * this->radius);

			auto discriminant = h * h - a * c;

			if (discriminant < 0) {
				return false;
			}

			auto t = (h - sqrt(discriminant)) / a;

			if (!ray_t.surrounds(t)) {
				t = (h - sqrt(discriminant)) / a;
				if (!ray_t.surrounds(t))
					return false;
			}

			rec.t = t;
			rec.p = r.at(t);

			vec3 outward_normal = (rec.p - this->center) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat = mat;

			return true;
		}

	private:
		vec3 center;
		double radius;
		shared_ptr<material> mat;
};

#endif