# Secure Sense
A smart security system for protecting valuable items, developed by MOCH Electronics as part of the Electronics and Arduino Programming Training by TME Education at Qubix Robotics, Blantyre, Malawi.

# How it works
Secure Sense is a smart security system designed to protect valuable items using motion detection, distance sensing, and automated access control. The system continuously monitors the area around a protected item and reacts based on threat level. When an unauthorized person enters the warning zone, the system begins emitting slow beeps. As the person moves closer, the beeping becomes faster, signaling increased risk. If motion is detected within the restricted zone, indicating a possible theft attempt, the system triggers a continuous alarm and automatically locks the room by closing the door, preventing the intruder from escaping.

The system also displays real-time security status updates on an LCD screen, including warnings, intrusion alerts, and fire detection events. Additionally, a flame sensor is integrated to detect fire hazards and trigger an emergency alarm.

Authorized users can safely access or store items by pressing a control button, which toggles the system state and allows the door to open. While the current version provides on-device alerts via an LCD, future improvements could include real-time mobile notifications for remote monitoring.

# Sensors and Actuators
Secure Sense uses a combination of sensors and actuators to detect threats, trigger alerts, and control physical access to protected items.

### Sensors
1. Motion Sensor (PIR): Detects movement near the protected area and triggers an intrusion state when unauthorized motion is detected.
2. Ultrasonic Sensor: Measures the distance between a person and the protected item to determine warning and danger levels based on proximity.
3. Flame Sensor: Detects fire hazards and activates an emergency alarm state.
4. Push Button: Allows authorized users to toggle system access, enabling safe retrieval or storage of items.

### Actuators
1. Buzzer / Speaker: Produces different alarm patterns depending on the system state, including warning beeps, danger alerts, continuous intrusion alarms, and fire alerts.
2. Servo Motor: Controls the door lock mechanism by opening access for authorized users and automatically locking the room during intrusion events.
3. LCD Display (I2C): Provides real-time visual feedback on system status, such as active mode, warnings, intrusion alerts, and fire detection

# Team
Secure Sense was developed as a group project by Maxwell, Owen, Christian, and Hope, collectively operating under the name MOCH Electronics, an acronym derived from the first letters of each member’s name. The team was selected by the instructors of the Electronics and Arduino Programming Training to collaborate on the design and implementation of this project.

