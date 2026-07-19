class Camera {
public:
  vec3 pos{0, 0, 3};
  vec3 dir{};
  void get_view_matrix(mat4* dest);
};

void Camera::get_view_matrix(mat4* dest) {
  glm_lookat(pos, dir, GLM_YUP, *dest);
}
