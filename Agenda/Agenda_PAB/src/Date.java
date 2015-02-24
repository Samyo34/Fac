import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.text.DateFormat;

//http://www.tom2ade.univ-montp2.fr/jsp/custom/modules/plannings/anonymous_cal.jsp?resources=2471,3161,3213,3216,3299&projectId=12&calType=ical&firstDate=2015-02-23&lastDate=2015-03-01
public class Date {
	
	public GregorianCalendar calendar;
	
	public Date(){
		calendar  = new java.util.GregorianCalendar();
	}
	
	/*
	 * Retourne une String au format de l'addresse http donnant la date de début de la semaine actuel
	 */
	public String getDateDeb(){
		java.util.Date d= calendar.getTime();
		
		Locale locale = Locale.getDefault();
		DateFormat dateFormat = DateFormat.getDateInstance(DateFormat.FULL, locale);
		String date = dateFormat.format(d);
		String[] sp = date.split(" ");
		calendar.getTime();
		switch(sp[0]){
			case "mardi":
				calendar.add(Calendar.DATE, -1);// on remonte d'un jour;
				break;
			case "mercredi":
				calendar.add(Calendar.DATE, -2);
				break;
			case "jeudi":
				calendar.add(Calendar.DATE, -3);
				break;
			case "vendredi":
				calendar.add(Calendar.DATE, -4);
				break;
			case "samedi":
				calendar.add(Calendar.DATE, -5);
				break;
			case "dimanche":
				calendar.add(Calendar.DATE, 1);
				break;
		}
				
			
		
		
		
		String year = Integer.toString((calendar.get(Calendar.YEAR)));
		String month = Integer.toString((calendar.get(Calendar.MONTH)+1));
		String day = Integer.toString((calendar.get(Calendar.DAY_OF_MONTH)));
		if(month.length()<2){
			month = "0"+month;
		}
		if(day.length()<2){
			day = "0"+day;
		}
		
		return year+"-"+month+"-"+day;
	}
	
	
	/*
	 * Retourne une String au format de l'addresse http donnant la date de fin de la semaine actuel
	 */
	public String getDateFin(){
		java.util.Date d= calendar.getTime();
		
		Locale locale = Locale.getDefault();
		DateFormat dateFormat = DateFormat.getDateInstance(DateFormat.FULL, locale);
		String date = dateFormat.format(d);
		String[] sp = date.split(" ");
		calendar.getTime();
		switch(sp[0]){
			case "mardi":
				calendar.add(Calendar.DATE, 5);// on avance de 5 jours;
				break;
			case "mercredi":
				calendar.add(Calendar.DATE, 4);
				break;
			case "jeudi":
				calendar.add(Calendar.DATE, 3);
				break;
			case "vendredi":
				calendar.add(Calendar.DATE, 2);
				break;
			case "samedi":
				calendar.add(Calendar.DATE, 1);
				break;
			case "lundi":
				calendar.add(Calendar.DATE, 6);
				break;
		}
				
			
		
		
		
		String year = Integer.toString((calendar.get(Calendar.YEAR)));
		String month = Integer.toString((calendar.get(Calendar.MONTH)+1));
		String day = Integer.toString((calendar.get(Calendar.DAY_OF_MONTH)));
		if(month.length()<2){
			month = "0"+month;
		}
		if(day.length()<2){
			day = "0"+day;
		}
		
		return year+"-"+month+"-"+day;
	}
	

}
