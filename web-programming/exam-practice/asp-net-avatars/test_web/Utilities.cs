namespace test_web
{
	public static class Utilities
	{
		public static List<int> stringToListOfInts(string stringForm)
		{
			return stringForm.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries)
							   .Select(int.Parse)
							   .ToList();
		}
		public static string listOfIntsToString(List<int> theInts)
		{
			return string.Join(",", theInts) + ",";
		}
	}
}
