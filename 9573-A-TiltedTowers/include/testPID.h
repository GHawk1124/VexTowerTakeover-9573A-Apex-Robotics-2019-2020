class pid_controller {
public:
  void init();

  pid_controller(float _pidTarget, float _Kp, float _Ki, float _Kd);

protected:
  const float pidTarget;

  const float Kp;
  const float Ki;
  const float Kd;

  float pidError;
  float pidLastError;
  float pidIntegral;
  float pidDerivative;

private:
  void run(float pidTarget);
};