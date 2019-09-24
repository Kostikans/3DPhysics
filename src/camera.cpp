#include "camera.h"
#include <QtMath>

Camera::Camera(QVector3D position, QVector3D up, float yaw, float pitch)
    : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = QVector3D(posX, posY, posZ);
    WorldUp = QVector3D(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Direction::Camera_Movement direction)
{
    float velocity = MovementSpeed;
    if (direction == Camera_Direction::Camera_Movement::FORWARD)
        Position += Front * velocity;
    if (direction == Camera_Direction::Camera_Movement::BACKWARD)
        Position -= Front * velocity;
    if (direction == Camera_Direction::Camera_Movement::LEFT)
        Position -= Right * velocity;
    if (direction == Camera_Direction::Camera_Movement::RIGHT)
        Position += Right * velocity;


}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
   // qDebug() << xoffset;
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += -yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= yoffset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{

    QVector3D front;
    front.setX(cosf(qDegreesToRadians(Yaw)) * cosf(qDegreesToRadians(Pitch)));
    front.setY(sinf(qDegreesToRadians(Pitch)));
    front.setZ(sinf(qDegreesToRadians(Yaw)) * cosf(qDegreesToRadians(Pitch)));
    Front = front.normalized();

    Right = QVector3D::crossProduct(Front, WorldUp);
    Right.normalize();
    Up = QVector3D::crossProduct(Right, Front);
    Up.normalize();
}

void Camera::draw(QOpenGLShaderProgram *shaderProgram)
{
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.lookAt(Position, Position + Front, Up);
    shaderProgram->setUniformValue("viewMatrix", viewMatrix);
    shaderProgram->setUniformValue("u_eyePosition", Position);
}

