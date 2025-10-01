var sheet_id = "1_x56ULDeZt0T7jPo90Gc4AyTz3WVp46lA2sGsh0tD8s";  
var sheet_name = "Sheet1";         

function doGet(e) {
  var ss = SpreadsheetApp.openById("1_x56ULDeZt0T7jPo90Gc4AyTz3WVp46lA2sGsh0tD8s");
  var sheet = ss.getSheetByName("Sheet1");

  var date   = e.parameter.date   || "";
  var analog = e.parameter.analog || "";
  var temp   = e.parameter.temp   || "";

  // ตรงกับหัวตาราง: Date | analog | Temp
  sheet.appendRow([date, analog, temp]);

  return ContentService.createTextOutput(
    "Data added: " + date + ", " + analog + ", " + temp
  );
}
