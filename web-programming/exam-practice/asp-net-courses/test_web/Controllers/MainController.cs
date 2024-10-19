using System.Text.Json;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using test_web.Data;
using test_web.Models;

namespace test_web.Controllers
{
	public class MainController : Controller
	{
		private readonly MyDbContext _context;

		public MainController(MyDbContext context)
		{
			_context = context;
		}

		public IActionResult Index()
		{
			return View("Index", HttpContext.Session.GetString("username"));
		}

		public string Test()
		{
			return "It's working";
		}

		public string GetCourses()
		{
			List<Course> courses = _context.Courses.ToList();

			string result = "<table><thead><th>Id</th><th>Professor</th><th>Name</th><th>Participants</th><th>Grades</th></thead>";

			foreach (Course course in courses)
			{
				result += "<tr><td>" + course.Id + "</td><td>" +
					_context.Persons.First(person => person.Id == course.ProfessorId).Name + "</td><td>" +
					course.CourseName + "</td><td>" + course.Participants + "</td><td>" + course.Grades + "</td></tr>";
			}

			result += "</table>";
			return result;
		}

		public string GetStudents()
		{
			List<Person> students = _context.Persons.Where(person => person.Role == "student").ToList();

			string result = "<table><thead><th>Id</th><th>Name</th></thead>";

			foreach (Person student in students)
			{
				result += "<tr><td>" + student.Id + "</td><td>" + student.Name + "</td></tr>";
			}

			result += "</table>";
			return result;
		}

		public string GetCoursesComboboxOptions()
		{
			List<Course> courses = _context.Courses.ToList();

			string result = "";

			foreach (Course course in courses)
			{
				result += "<option value='" + course.Id + "'>" + course.CourseName + "</option>";
			}

			return result;
		}

		public string GetMyCoursesComboboxOptions()
		{
			int? myId = HttpContext.Session.GetInt32("user_id");

			if (myId == null)
				return "You haven't entered your name.";

			List<Course> courses = _context.Courses.Where(course => course.ProfessorId == myId).ToList();

			string result = "";

			foreach (Course course in courses)
			{
				result += "<option value='" + course.Id + "'>" + course.CourseName + "</option>";
			}

			return result;
		}

		public string GetStudentsComboboxOptions()
		{
			List<Person> students = _context.Persons.Where(person => person.Role == "student").ToList();

			string result = "";

			foreach (Person student in students)
			{
				result += "<option value='" + student.Id + "'>" + student.Name + "</option>";
			}

			return result;
		}

		public string GetCourseParticipants(int courseId)
		{
			var course = _context.Courses.Find(courseId);
			if (course == null)
				return "No such course.";

			List<int> participantIds = JsonSerializer.Deserialize<List<int>>(course.Participants);
			List<Person> participants = _context.Persons.Where(person => participantIds.Contains(person.Id)).ToList();

			string result = "<table><thead><th>Id</th><th>Name</th><th>Role</th></thead>";

			foreach (Person participant in participants)
			{
				result += "<tr><td>" + participant.Id + "</td><td>" + participant.Name + "</td><td>" +
					participant.Role + "</td></tr>";
			}

			result += "</table>";
			return result;
		}

		public string GetStudentCourses(int studentId)
		{
			var student = _context.Persons.Find(studentId);
			if (student == null || student.Role != "student")
				return "No such student.";

			string result = "<table><thead><th>Course Id</th><th>Course Name</th><th>Professor</th></thead>";

			List<Course> allCourses = _context.Courses.ToList();
			foreach (Course course in allCourses)
			{
				List<int> participantIds = JsonSerializer.Deserialize<List<int>>(course.Participants);

				if (participantIds.Contains(studentId))
				{
					result += "<tr><td>" + course.Id + "</td><td>" + course.CourseName + "</td><td>" +
							_context.Persons.First(person => person.Id == course.ProfessorId).Name + "</td></tr>";
				}
			}

			result += "</table>";
			return result;
		}

		public IActionResult AddGrade(int studentId, int courseId, int grade)
		{
			var course = _context.Courses.Find(courseId);
			if (course == null)
			{
				return NotFound("No such course.");
			}

			var student = _context.Persons.Find(studentId);
			if (student == null || student.Role != "student")
			{
				return NotFound("No such student.");
			}

			if (course.ProfessorId != HttpContext.Session.GetInt32("user_id"))
				return BadRequest("This isn't your course.");

			if (!isGradeValid(grade))
			{
				return BadRequest("Grade should be between 1 and 10");
			}

			List<int> participantIds = JsonSerializer.Deserialize<List<int>>(course.Participants);

			// if not participant, add it to participants
			if (!participantIds.Contains(studentId))
			{
				participantIds.Add(studentId);
				course.Participants = JsonSerializer.Serialize(participantIds);
			}

			Dictionary<int, int> grades = JsonSerializer.Deserialize<Dictionary<int, int>>(course.Grades);

			// add/update grade
			grades[studentId] = grade;
			course.Grades = JsonSerializer.Serialize(grades);

			_context.SaveChanges();

			return Ok("Grade added or updated successfully.");
		}

		private bool isGradeValid(int grade)
		{
			return 1 <= grade && grade <= 10;
		}


	}
}
