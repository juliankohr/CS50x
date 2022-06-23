# Beck-Depression-Inventory-Platform
#### Video Demo:  https://youtu.be/HwwVBMYB53c
#### Description:

During psychotherapy, a wide variety of tests are often used to measure the course and success of the therapy.
The tests are often handed to you as a paper document at the end of a therapy session. However, this has some disadvantages, since the documents can be lost and must be evaluated and documented manually by the therapist.
To make this easier, I developed the Beck Depression Inventory Platform, which connects patients and therapists and digitizes the tests, including the evaluations.

Therapists and patients register on the platform.
The therapists can set their party tests, which can be processed on any device.
After sending, the therapist receives the evaluated result directly and can display statistics for the tests over time.
This means that less time has to be spent on evaluation and the therapists have more time for more important things.


#### Walktrough

The user has to register first, either as patient or therapist.
It's crucial for the functionality of the platform to devide users into those two roles.

The UI of the patient is quite simple.
It has an empty state to tell the user if no test was sent by a therapist yet.
It is also possible to see a history of past tests, to get imformation about the account and to log out.
If a therapist sent a test to the patient he or she is able to answer all 21 questions of the BDI-II test.

For therapists the UI is a bit extended.
In the history tab the therapist sees when tests got sent out to patients.
Account informations are also available as well as the functionality to log out.
Additional functionalities are the sending of tests to patients and the resulsts tab.
for sending a test, the therapist just has to select a patient from the drop down menue.
Based on the received results of several tests, the therapist is able to get a result chart for every patient.


#### Technical Details:

This flask based app makes use of Bootstrap for the UI elements, an SQL database to store user/test data and python for evaluating the questionaire.
Chart.js is used to show a graph based on score and sent date of the test.


#### Outlook

In future versions it could be possible to include more tests, that are common in psychotherapy.
Also more detailed statistics to compare not only tests, but also several domains that could be a reason for a depression. (differs from patient to patient)
Patients could be individually assigned to one specific therapist.


#### Testimonial:

I want to thank Davi J. Malan and the whole CS50 team for making this great class possible.
