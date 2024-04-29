# Project (SCM & SDLC)
## Online Exam Seating Plan
### Muhammad Rameez & Mehtab Khaki
#### SET-06 & SET-10

#### Functional Requirements:
1. User Role Management
2. User Authentication and Authorization
3. Student Enrollment and Registration
4. Automated Notifications
5. Mobile Compatibility
6. Integration with Other Systems
7. Reporting and Analytics
8. Accessibility Features
9. Conflict Resolution
10. Seating Arrangement Generation
11. Seating Plan Management
12. Seating Plan Display
13. Seating Plan Printing Options
14. Customizable Seating Templates
15. Seating Plan History
16. Scalability and Performance
17. Data Backup and Recovery
18. User Interface Customization
19. Audit Trail Logging

#### Priority Based Table:
| Priority | Functionality                           | Description                                                                                                                                                                        |
|----------|-----------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1        | User Authentication and Authorization  | Students and instructors must securely log in using a username and password or other secure method. The system should enforce user roles and permissions to restrict access to sensitive data and functionalities. |
| 2        | Data Backup and Recovery               | The system should implement mechanisms for backing up critical data (student information, exam details, seating plans) and recovering it in case of system failures.                   |
| 3        | Scalability and Performance           | The system should be able to handle a large number of concurrent users and exams without compromising performance. This is crucial to ensure a smooth exam experience for everyone. |
| 4        | Seating Plan Management               | The system should allow for creating, editing, and managing seating plans for different exams. This may include defining exam rooms, seating capacities, and assigning special seating arrangements for students with disabilities. |
| 5        | Conflict Resolution                   | (Medium Priority) The system should be able to identify and address conflicts that may arise during seating plan generation, such as students with overlapping exams or special seating requirements. |
| 6        | Seating Arrangement Generation        | (Medium Priority) The system should automatically generate seating plans that minimize the risk of cheating. This may involve using algorithms to consider factors like student spacing, avoiding seating next to classmates, and potentially rotating seating based on pre-defined criteria. |
| 7        | Reporting and Analytics              | (Medium Priority) The system should generate reports on exam results, such as average scores and student performance analysis. This can help identify potential cheating or areas for improvement in the exam process. |
| 8        | Integration with Other Systems        | (Lower Priority) The system should integrate with other relevant systems, such as learning management systems (LMS) to import exam data and student information systems to synchronize student enrollment data. However, this can be implemented in later phases to prioritize core functionalities. |
| 9        | User Role Management and Audit Trail Logging | (Lower-Medium Priority) * User Role Management: The system should allow for defining and managing user roles with different access levels and permissions. This ensures only authorized users can access specific functionalities. * Audit Trail Logging: The system should log user activities related to exam creation, seating plan management, and student enrollment. This helps maintain auditability and identify potential security breaches. |
| 10       | Login                                 | This functionality is likely part of User Authentication and Authorization (priority 1).                                                                                          |
| 11       | Seating Plan Display                  | Students should be able to view their assigned seat location within the exam room after registering for an exam.                                                                    |
| 12       | Student Enrollment and Registration   | Students should be able to register for exams through a user-friendly interface. The system may integrate with student information systems to streamline the enrollment process.         |
| 13       | User Interface Customization         | (Low Priority) The system should allow for some level of user interface customization to personalize the user experience.                                                          |
| 14       | Mobile Compatibility                  | (Low Priority) The system should be accessible from mobile devices for functionalities like student enrollment and viewing seating assignments.                                   |
| 15       | Automatic Notifications               | (Low Priority) The system can optionally send automated notifications to students and instructors regarding exam registration deadlines, seating assignments, or exam updates.     |
| 16       | Accessibility Features                | (Lowest Priority) The system should comply with accessibility standards to ensure equal access for students with disabilities. This may include features like screen reader compatibility, keyboard navigation, and alternative text descriptions for images. |
| 17       | Seating Plan Printing Options         | (Lowest Priority) The system could offer an optional functionality to print seating plans for exam administrators or reference purposes.                                             |
| 18       | Customizable Seating Templates       | (Lowest Priority) The system could allow for creating and using custom seating templates for specific exam needs or room layouts.                                                      |
| 19       | Seating Plan History                  | (Lowest Priority) The system could optionally track and maintain a history of past exam seating plans for reference or auditing purposes.                                                 |