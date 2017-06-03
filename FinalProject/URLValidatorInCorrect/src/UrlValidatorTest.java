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
   
   public void testManualTest()
   {
	   UrlValidator uVal = new UrlValidator(new String[] {"http", "gopher"}, 0);
	   UrlValidator uVal2 = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
	   
	   assertEquals(uVal.isValid("http://a.m.a.z.o.n.com"), true);
	   assertEquals(uVal.isValid("http://www.a.m.a.z.o.n.com"), true);
	   assertEquals(uVal.isValid("http://www.reallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurlreallylongurl.com"), true);
	   assertEquals(uVal.isValid("http://www.semicolonandunderscoresinpath.com/path;_123sdfjni"), true);
	   assertEquals(uVal.isValid("http://www.parentheses.com/copyofcopyofEssay(1).docx"), true);
	   assertEquals(uVal.isValid("http://www.google.com:80/test1?action=view true"), true);
	   assertEquals(uVal.isValid("http://0.0.0.0:80/test1?action=view true"), true);
	   assertEquals(uVal.isValid("http://localhost:80"), false);
	   assertEquals(uVal2.isValid("http://localhost:80"), true);
	   assertEquals(uVal.isValid("http://hostname:80"), false);
	   assertEquals(uVal2.isValid("http://hostname:80"), true);
   }                            
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
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
