/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   private boolean logMismatched(UrlValidator uVal, String url, boolean exResult) {
	   boolean result = uVal.isValid(url);
	   if (result != exResult) {
		   System.out.println("Error: " + url);
		   return false;
	   }
	   return true;
   }
   
   public void testManualTest()
   {
	   UrlValidator uVal = new UrlValidator(new String[] {"http", "gopher"}, 0);
	   UrlValidator uVal2 = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
	   
	   System.out.println("--- Manual tests ---");
	   boolean passed = true;
	   passed &= logMismatched(uVal, "", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:80/path?q=query&q2=this", true);
	   passed &= logMismatched(uVal, "www.amazon.com:80/path?q=query&q2=this", false);
	   passed &= logMismatched(uVal, "http://:80/path?q=query&q2=this", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com/path?q=query&q2=this", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:80/?q=query&q2=this", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:80/path?q=query", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:80/path", true);
	   passed &= logMismatched(uVal, "htt://www.amazon.com", false);
	   passed &= logMismatched(uVal, "http//www.amazon.com", false);
	   passed &= logMismatched(uVal, "http:/www.amazon.com", false);
	   passed &= logMismatched(uVal, "0http://www.amazon.com", false);
	   passed &= logMismatched(uVal, "htt0p://www.amazon.com", false);
	   passed &= logMismatched(uVal, "HTTP://www.amazon.com", true);
	   passed &= logMismatched(uVal, "http://amazon.com", true);
	   passed &= logMismatched(uVal, "http://www.com", true);
	   passed &= logMismatched(uVal, "http://www.amazon", false);
	   passed &= logMismatched(uVal, "http://amazon", false);
	   passed &= logMismatched(uVal, "http://www.AMAZON.com", true);
	   passed &= logMismatched(uVal, "http://www.0amazon.com", true);
	   passed &= logMismatched(uVal, "http://www.amaz0n.com", true);
	   passed &= logMismatched(uVal, "http://www.amazon.5", false);
	   passed &= logMismatched(uVal, "http://0.0.00.0", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:nan", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com:65535", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:65536", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:65537", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:54.43", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com:-5", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com:0", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/0544", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/PATH", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/-p", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/pa:th", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/path/", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/longer/path", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/pa//th", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com//path", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com/ /", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com/?basic=query", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/?basic=222", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/?000=query", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/?basic", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/?basic=", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/?basic=&q=none", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/&query", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/?=query", true);
	   
	   passed &= logMismatched(uVal, "http://www.amazon.com", true);
	   passed &= logMismatched(uVal, "http://", false);
	   passed &= logMismatched(uVal, "aaa://www.amazon.com", false);
	   passed &= logMismatched(uVal, "www.amazon.com", false);
	   passed &= logMismatched(uVal, "amazon.com", false);
	   passed &= logMismatched(uVal, "amazon.com:80", false);
	   passed &= logMismatched(uVal, "amazon.com:80/abc", false);
	   passed &= logMismatched(uVal, "http://www.a mazon.com", false);
	   passed &= logMismatched(uVal, "http://www.com", true);
	   passed &= logMismatched(uVal, "http://www..com", false);
	   passed &= logMismatched(uVal, "http://www._.com", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com:80/abc", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com:-1/abc", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com:80.1/abc", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com:a/abc", false);
	   passed &= logMismatched(uVal, "http://www.amazon.com:80/1", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com/1", true);
	   passed &= logMismatched(uVal, "http://www.amazon.com.", false);
	   
	   passed &= logMismatched(uVal, "http://a.m.a.z.o.n.com", true);
	   passed &= logMismatched(uVal, "http://www.a.m.a.z.o.n.com", true);
	   passed &= logMismatched(uVal, "http://www.reallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurl.com", true);
	   passed &= logMismatched(uVal, "http://www.semicolonandunderscoresinpath.com/path;_123sdfjni", true);
	   passed &= logMismatched(uVal, "http://www.parentheses.com/copyofcopyofEssay(1).docx", true);
	   passed &= logMismatched(uVal, "http://www.google.com:80/test1?action=view true", true);
	   passed &= logMismatched(uVal, "http://0.0.0.0:80/test1?action=view true", true);
	   passed &= logMismatched(uVal, "http://localhost:80", false);
	   passed &= logMismatched(uVal2, "http://localhost:80", true);
	   passed &= logMismatched(uVal, "http://hostname:80", false);
	   passed &= logMismatched(uVal2, "http://hostname:80", true);
	   
	   assertTrue(passed); // perform all calculations first (&= doesn't shortcircuit) then perform the test
   }                            
   
   
   public void testSchemePartition()
   {
	   UrlValidator uVal = new UrlValidator(new String[] {"http"}, 0);

	   System.out.println("--- Scheme partition ---");
	   boolean passed = true;
	   passed &= logMismatched(uVal, "http://www.go.com", true);
	   passed &= logMismatched(uVal, "www.go.com", true);
	   passed &= logMismatched(uVal, "HTTP://www.go.com", true);
	   passed &= logMismatched(uVal, "htt://www.go.com", false);
	   passed &= logMismatched(uVal, "aaa://www.go.com", false);
	   passed &= logMismatched(uVal, "://www.go.com", false);
	   passed &= logMismatched(uVal, "http:/www.go.com", false);
	   
	   assertTrue(passed);
   }
   
   public void testAuthorityPartition(){
	   UrlValidator uVal = new UrlValidator(new String[] {"http"});
	   
	   System.out.println("--- Authority partition ---");
	   boolean passed = true;
	   passed &= logMismatched(uVal, "http://www.go.com", true);
	   passed &= logMismatched(uVal, "http://", false);
	   passed &= logMismatched(uVal, "http://WWW.GO.COM", true);
	   passed &= logMismatched(uVal, "http://go.com", true);
	   passed &= logMismatched(uVal, "http://www.go", false);
	   passed &= logMismatched(uVal, "http://localhost", false);
	   passed &= logMismatched(uVal, "http://0.0.0.0", true);
	   passed &= logMismatched(uVal, "http://255.255.255.255", true);
	   passed &= logMismatched(uVal, "http://255.255.255.256", false);
	   
	   assertTrue(passed);
   }
   
   public void testPortPartition(){
	   UrlValidator uVal = new UrlValidator(new String[] {"http"});
	   
	   System.out.println("--- Port Partition ---");
	   boolean passed = true;
	   passed &= logMismatched(uVal, "http://www.go.com:80", true);
	   passed &= logMismatched(uVal, "http://www.go.com", true);
	   passed &= logMismatched(uVal, "http://www.go.com:-1", false);
	   passed &= logMismatched(uVal, "http://www.go.com:65536", true);
	   
	   assertTrue(passed);
   }

   public void testPathPartition(){
	   UrlValidator uVal = new UrlValidator(new String[] {"http"});
	   
	   System.out.println("--- Path partition ---");
	   boolean passed = true;
	   passed &= logMismatched(uVal, "http://www.go.com/path", true);
	   passed &= logMismatched(uVal, "http://www.go.com/PATH", true);
	   passed &= logMismatched(uVal, "http://www.go.com", true);
	   
	   assertTrue(passed);
   }

   public void testQueryPartition(){
	   UrlValidator uVal = new UrlValidator(new String[] {"http"});
	   
	   System.out.println("--- Query partition ---");
	   boolean passed = true;
	   passed &= logMismatched(uVal, "http://www.go.com?q=query", true);
	   passed &= logMismatched(uVal, "http://www.go.com?Q=QUERY", true);
	   passed &= logMismatched(uVal, "http://www.go.com", true);
	   
	   assertTrue(passed);
   }

   public void testFlagsPartition(){
	   // ALLOW_ALL_SCHEMES = true
	   UrlValidator uVal = new UrlValidator(new String[] {"http"}, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("--- Flags partition - Schemes ---");
	   boolean passed = true;
	   passed &= logMismatched(uVal, "http://www.go.com", true);
	   passed &= logMismatched(uVal, "aaa://www.go.com", true);
	   passed &= logMismatched(uVal, "://www.go.com", false);
	   
	   // ALLOW_LOCAL_URLS = true
	   uVal = new UrlValidator(new String[] {"http"}, UrlValidator.ALLOW_LOCAL_URLS);
	   
	   System.out.println("--- Flags partition - Local Urls ---");
	   passed &= logMismatched(uVal, "http://www.go.com", true);
	   passed &= logMismatched(uVal, "http://localhost", true);
	   
	   assertTrue(passed);
   }
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
