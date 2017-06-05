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
	   
	   assertEquals(uVal.isValid(""), false);
	   assertEquals(uVal.isValid("http://www.amazon.com"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:80/path?q=query&q2=this"), true);
	   assertEquals(uVal.isValid("www.amazon.com:80/path?q=query&q2=this"), false);
	   assertEquals(uVal.isValid("http://:80/path?q=query&q2=this"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com/path?q=query&q2=this"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:80/?q=query&q2=this"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:80/path?q=query"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:80/path"), true);
	   assertEquals(uVal.isValid("htt://www.amazon.com"), false);
	   assertEquals(uVal.isValid("http//www.amazon.com"), false);
	   assertEquals(uVal.isValid("http:/www.amazon.com"), false);
	   assertEquals(uVal.isValid("0http://www.amazon.com"), false);
	   assertEquals(uVal.isValid("htt0p://www.amazon.com"), false);
	   assertEquals(uVal.isValid("HTTP://www.amazon.com"), true);
	   assertEquals(uVal.isValid("http://amazon.com"), true);
	   assertEquals(uVal.isValid("http://www.com"), true);
	   assertEquals(uVal.isValid("http://www.amazon"), false);
	   assertEquals(uVal.isValid("http://amazon"), false);
	   assertEquals(uVal.isValid("http://www.AMAZON.com"), true);
	   assertEquals(uVal.isValid("http://www.0amazon.com"), true);
	   assertEquals(uVal.isValid("http://www.amaz0n.com"), true);
	   assertEquals(uVal.isValid("http://www.amazon.5"), false);
	   assertEquals(uVal.isValid("http://0.0.00.0"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:nan"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com:65535"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:65536"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:65537"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:54.43"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com:-5"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com:0"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/0544"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/PATH"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/-p"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/pa:th"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/path/"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/longer/path"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/pa//th"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com//path"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com/ /"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com/?basic=query"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/?basic=222"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/?000=query"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/?basic"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/?basic="), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/?basic=&q=none"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/&query"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/?=query"), true);
	   
	   assertEquals(uVal.isValid("http://www.amazon.com"), true);
	   assertEquals(uVal.isValid("http://"), false);
	   assertEquals(uVal.isValid("aaa://www.amazon.com"), false);
	   assertEquals(uVal.isValid("www.amazon.com"), false);
	   assertEquals(uVal.isValid("amazon.com"), false);
	   assertEquals(uVal.isValid("amazon.com:80"), false);
	   assertEquals(uVal.isValid("amazon.com:80/abc"), false);
	   assertEquals(uVal.isValid("http://www.a mazon.com"), false);
	   assertEquals(uVal.isValid("http://www.com"), true);
	   assertEquals(uVal.isValid("http://www..com"), false);
	   assertEquals(uVal.isValid("http://www._.com"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com:80/abc"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com:-1/abc"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com:80.1/abc"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com:a/abc"), false);
	   assertEquals(uVal.isValid("http://www.amazon.com:80/1"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com/1"), true);
	   assertEquals(uVal.isValid("http://www.amazon.com."), false);
	   
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
