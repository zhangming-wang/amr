from ultralytics import YOLO
import cv2

# 1. 加载模型
# 如果是 pt 权重
model = YOLO("/home/dev/workspace/amr/ros2_master/src/control/control_panel/src/model/yolov5lu.pt")

# 如果是 onnx 模型
# model = YOLO("/home/dev/workspace/amr/ros2_master/src/control/control_panel/src/model/yolov5lu.onnx")

# 2. 读取图片
img_path = "/home/dev/workspace/amr/test/yolo_test/bird.jpg"
img = cv2.imread(img_path)

# 3. 预测
results = model.predict(source=img, imgsz=640)  # 返回 Results 对象

# 4. 可视化
annotated_frame = results[0].plot()  # 返回绘制了 bbox 的 numpy 图像

cv2.imshow("YOLO Detection", annotated_frame)
cv2.waitKey(0)
cv2.destroyAllWindows()
