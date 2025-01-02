#include "FreeRTOS.h"
#include "task.h"

#define TF_LITE_STATIC_MEMORY 1

#include <math.h>

#include "tensorflow/lite/core/c/common.h"
#include "models/hello_world_float_model_data.h"
#include "models/hello_world_int8_model_data.h"
#include "micro/micro_interpreter.h"
#include "micro/micro_log.h"
#include "micro/micro_mutable_op_resolver.h"
#include "micro/micro_profiler.h"
#include "micro/recording_micro_interpreter.h"
#include "micro/system_setup.h"
#include "schema/schema_generated.h"
#include "tflite_learn_3.h"

extern unsigned char g_model[];
namespace
{
  using HelloWorldOpResolver = tflite::MicroMutableOpResolver<1>;

  TfLiteStatus RegisterOps(HelloWorldOpResolver &op_resolver)
  {
    TF_LITE_ENSURE_STATUS(op_resolver.AddFullyConnected());
    return kTfLiteOk;
  }
} // namespace

int main(int argc, char *argv[])
{
  tflite::InitializeTarget();
  const tflite::Model *model =
      ::tflite::GetModel(g_model);
  TFLITE_CHECK_EQ(model->version(), TFLITE_SCHEMA_VERSION);

  HelloWorldOpResolver op_resolver;
  TF_LITE_ENSURE_STATUS(RegisterOps(op_resolver));

  // Arena size just a round number. The exact arena usage can be determined
  // using the RecordingMicroInterpreter.
  constexpr int kTensorArenaSize = 57000;
  uint8_t tensor_arena[kTensorArenaSize];

  tflite::MicroInterpreter interpreter(model, op_resolver, tensor_arena,
                                       kTensorArenaSize);
  // TF_LITE_ENSURE_STATUS(interpreter.AllocateTensors());
  if (interpreter.AllocateTensors() != kTfLiteOk)
  {
    printf("Allocation Failed!\n");
  }

  // Check if the predicted output is within a small range of the
  // expected output
  float epsilon = 0.05f;
  constexpr int kNumTestValues = 4;
  float golden_inputs[kNumTestValues] = {0.f, 1.f, 3.f, 5.f};

  TfLiteType t = interpreter.input(0)->type;

  for (int i = 0; i < kNumTestValues; ++i)
  {
    interpreter.input(0)->data.f[0] = golden_inputs[i];
    TF_LITE_ENSURE_STATUS(interpreter.Invoke());
    float y_pred = interpreter.output(0)->data.f[0];
    // TFLITE_CHECK_LE(abs(sin(golden_inputs[i]) - y_pred), epsilon);
  }

  while (true)
  {
    /* code */
  }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) // Stack Overflow Hook
{
  /* Print or log stack overflow for task debugging */
  for (;;)
    ; // Halt system to debug
}
