namespace test_web.Models
{
	public class Log
	{
		public int Id { get; set; }
		public DateTime Date { get; set; }
		public string Text { get; set; }

		public Log(DateTime date, string text)
		{
			Date = date;
			Text = text;
		}
	}
}
