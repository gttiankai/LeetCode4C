package payegis.com.jstest;

import android.webkit.JavascriptInterface;

/**
 * @ProjectName: JSTest
 * @Package: payegis.com.jstest
 * @Description:
 * @Author: Tiankai
 * @CreateDate: 2019-02-22 13:06
 * @UpdateUser:
 * @UpdateDate:
 * @UpdateRemark: The modified content
 * @Version: 1.0
 * <p>Copyright: Copyright (c) 2019</p>
 */
public class AndroidToJS {
    @JavascriptInterface
    public void hello(String msg) {
        System.out.println("JS调用了Android的hello方法");
    }
}
