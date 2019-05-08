# 3D Direction Vectors used by the Engine #
```
const Vector3 Vector3::FORWARD(0, 0, 1);
const Vector3 Vector3::BACKWARD(Vector3::FORWARD * -1);
const Vector3 Vector3::RIGHT(1, 0, 0);
const Vector3 Vector3::LEFT(Vector3::RIGHT * -1);
const Vector3 Vector3::UP(0, 1, 0);
const Vector3 Vector3::DOWN(Vector3::UP * -1);
```

# Euler Angles Represented by 3D Vectors #
### - The engine uses a ***Z-X-Y*** order:
|     Roll      |    Pitch      |  Yaw  |
|:-------------:|:-------------:|:-----:|
|      Z        |      X        |   Y   |

### - The engine views Euler angles as a clock-wise rotation around the ***positive*** end of the corresponding axis, therefore: ###
>Angle X = Pitch = -up / +down | Rotation around ```Vector3::LEFT```.
>
>Angle Y = Yaw   = -left / +right | Rotation around ```Vector3::UP```.
>
>Angle Z = Roll  = -left / +right | Rotation around ```Vector3::FORWARD```.

### - It is advised that when using the Vector3 structure to represent Euler angles, the ```pitch```, ```yaw```, and ```roll``` members are used as opposed to ```x```, ```y```, ```z```. ###

# Translations & Positions Represented by 3D Vectors #
## - The translations represented by 3D vectors correspond to the above direction vectors, therefore: ##
> Vector3(1, 0, 0) represents a translation of 1 unit ***right*** along the ***x-axis***.
> 
> Vector3(0, 1, 0) represents a translation of 1 unit ***up*** along the ***y-axis***.
> 
> Vector3(0, 0, 1) represents a translation of 1 unit ***forward*** along the ***z-axis***.
> 
> **Therefore, we use negative values to represent directions opposite of the directions shown above:**
> 
> Vector3(-1, 0, 0) represents a translation of 1 unit ***left*** along the ***x-axis***.
> 
> Vector3(0, -1, 0) represents a translation of 1 unit ***down*** along the ***y-axis***.
> 
> Vector3(0, 0, -1) represents a translation of 1 unit ***backward*** along the ***z-axis***.

### - A rotation matrix can be calculated from Euler angles as follows: ```Matrix4().Rotate(Vector3::LEFT, GetAngles().pitch).Rotate(Vector3::UP, GetAngles().yaw).Rotate(Vector3::FORWARD, GetAngles().roll)```, however it is recommended Quaternions and ```Quaternion::GetRotationMatrix()``` are used instead to avoid gimbal lock.

### - It is advised that when using the Vector3 structure to represent translations or positions in 3D space, the ```x```, ```y```, and ```z``` members are used.

# RGB Colors Represented by 3D Vectors #
### - It is advised that when using the Vector3 structure to represent translations or positions in 3D space, the ```r```, ```g```, and ```b``` members are used as opposed to ```x```, ```y```, ```z```. ###

### - Note that the engine provides ```Color4``` as an alternative to ```Vector4``` when trying to represent 8 byte RGBA (0-255) colors. It is important to note, however, that this ```Color4``` structure divides all colors by 255 when being explicitly or implicitly converted to a ```Vector4```. ###