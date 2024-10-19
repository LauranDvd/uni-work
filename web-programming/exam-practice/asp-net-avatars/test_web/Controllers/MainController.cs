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
			if (HttpContext.Session.GetString("username") == null)
				return RedirectToAction("Index", "Login"); // TODO guard all endpoints like this

			return View("Index", HttpContext.Session.GetString("username"));
		}

		public string Test()
		{
			return "It's working";
		}

		public string GetAvatars(int begin, int end)
		{
			List<Avatar> avatars = _context.Avatars.Where(avatar => begin <= avatar.Id && avatar.Id <= end).ToList();

			string result = "<table><thead><th>Id</th><th>Name</th><th>Age</th><th>Photo</th><th></th></thead>";

			foreach (Avatar avatar in avatars)
			{
				result += "<tr><td>" + avatar.Id + "</td><td>" +
					avatar.Name + "</td><td>" +
					avatar.Age + "</td><td><img width='100px' src='" + avatar.PhotoLink + "' /></td>" +
					"<td><button onclick='populateUpdateForm(" + avatar.Id + ", \"" + avatar.Name + "\", " + avatar.Age +
					")'>Update</button></td>" +
					"</tr>";
			}

			result += "</table>";
			return result;
		}

		public IActionResult AddAvatar(string name, int age, string link)
		{
			_context.Avatars.Add(new Avatar(name, age, link));
			_context.SaveChanges();

			addLog(DateTime.Now, new LogText("add", 0, name, age, link));

			return Ok("Avatar added successfully.");
		}

		private void addLog(DateTime dateTime, LogText text)
		{
			Console.Write($"adding with datetime={dateTime.ToString()}");
			// List<int> participantIds = JsonSerializer.Deserialize<List<int>>(course.Participants);
			string serializedText = JsonSerializer.Serialize(text);

			_context.Logs.Add(new Log(dateTime, serializedText));
			_context.SaveChanges();
		}

		public IActionResult UpdateAvatar(int id, string name, int age)
		{
			Avatar avatar = _context.Avatars.Find(id);

			if (avatar == null)
				return NotFound("No avatar with that ID");

			avatar.Name = name;
			avatar.Age = age;

			_context.SaveChanges();

			addLog(DateTime.Now, new LogText("update", id, name, age, avatar.PhotoLink));

			return Ok("Avatar updated successfully.");
		}
	}
}
